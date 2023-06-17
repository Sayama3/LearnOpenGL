//
// Created by ianpo on 16/06/2023.
//

#include <filesystem>
#include "Model.hpp"
#include "Logger.hpp"

Model::Model(const std::string &path) : m_Meshes(), m_Directory(path.substr(0, path.find_last_of('/'))) {
    LOG("Creating Model " + path);
    this->loadModel(path);
}

void Model::Draw(ShaderProgram &shader) {
    for (auto& mesh : m_Meshes) {
        mesh->Draw(shader);
    }
}

void Model::loadModel(const std::string &path) {
    LOG("Importing model");
    // Create an instance of the Importer class
    Assimp::Importer importer;

    // And have it read the given file with some example postprocessing
    // Usually - if speed is not the most important aspect for you - you'll
    // probably to request more postprocessing than we do in this example.
    const aiScene* scene = importer.ReadFile( path,
//                                              aiProcess_CalcTangentSpace        |
                                              aiProcess_Triangulate             |
//                                              aiProcess_JoinIdenticalVertices   |
//                                              aiProcess_GenNormals   |
                                              aiProcess_FlipUVs
//                                              aiProcess_SortByPType
                                              );

    // If the import failed, report it
    if (nullptr == scene) {
        LOG_ERROR(std::string("ERROR::ASSIMP::").append(importer.GetErrorString()));
        return;
    }

    m_Meshes.reserve(scene->mNumMeshes);


    LOG("Processing Root Node.");
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
    for (int i = 0; i < node->mNumMeshes; ++i) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        LOG(std::string("Adding mesh ").append(mesh->mName.C_Str()));
        m_Meshes.push_back(processMesh(mesh, scene));
    }

    for (int i = 0; i < node->mNumChildren; ++i) {
        LOG(std::string("Processing node children ").append(node->mChildren[i]->mName.C_Str()));
        processNode(node->mChildren[i], scene);
    }
}

std::shared_ptr<Mesh> Model::processMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertices;
    vertices.reserve(mesh->mNumVertices);
    std::vector<unsigned int> indices;
    indices.reserve(mesh->mNumFaces * 3);
    std::vector<std::shared_ptr<Texture2D>> textures;

    // Process Vertex
    LOG("Processing the " + std::to_string(mesh->mNumVertices) + "vertices.");
    for (int i = 0; i < mesh->mNumVertices; ++i) {
        Vertex vertex{};

        vertex.Position = {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z};

        vertex.Normal = {mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z};

        if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            vertex.TexCoords = {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y};
        }
        else
        {
            vertex.TexCoords = {0.0f, 0.0f};
        }

        vertices.push_back(vertex);
    }

    // Process Indices
    LOG("Processing the " + std::to_string(mesh->mNumFaces) + "faces.");
    for (int i = 0; i < mesh->mNumFaces; ++i) {
        auto& face = mesh->mFaces[i];
        for (int j = 0; j < face.mNumIndices; ++j) {
            indices.push_back(face.mIndices[j]);
        }
    }

    //process materials
    if(mesh->mMaterialIndex >= 0)
    {
        LOG(std::string("Processing Material of ").append(mesh->mName.C_Str()));
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];


        auto DIFFUSE_COUNT = material->GetTextureCount(aiTextureType::aiTextureType_DIFFUSE);
        auto SPECULAR_COUNT = material->GetTextureCount(aiTextureType::aiTextureType_SPECULAR);
        auto NORMALS_COUNT = material->GetTextureCount(aiTextureType::aiTextureType_NORMALS);
        auto HEIGHT_COUNT = material->GetTextureCount(aiTextureType::aiTextureType_HEIGHT);
        auto AMBIENT_COUNT = material->GetTextureCount(aiTextureType::aiTextureType_AMBIENT);
                ;
        textures.reserve(DIFFUSE_COUNT+SPECULAR_COUNT+NORMALS_COUNT+HEIGHT_COUNT+AMBIENT_COUNT);

        // 1. diffuse maps
        LOG("Adding " + std::to_string(DIFFUSE_COUNT) + " diffuse textures.");
        std::vector<std::shared_ptr<Texture2D>> diffuseMaps = loadMaterialTextures(material, aiTextureType::aiTextureType_DIFFUSE, TextureUsage::Diffuse);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // 2. specular maps
        LOG("Adding " + std::to_string(SPECULAR_COUNT) + " specular textures.");
        std::vector<std::shared_ptr<Texture2D>> specularMaps = loadMaterialTextures(material, aiTextureType::aiTextureType_SPECULAR, TextureUsage::Specular);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        // 3. normal maps
        LOG("Adding " + std::to_string(NORMALS_COUNT) + " normal textures.");
        std::vector<std::shared_ptr<Texture2D>> normalMaps = loadMaterialTextures(material, aiTextureType::aiTextureType_NORMALS, TextureUsage::Normal);
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        // 4. height maps
        LOG("Adding " + std::to_string(HEIGHT_COUNT) + " height textures.");
        std::vector<std::shared_ptr<Texture2D>> heightMaps = loadMaterialTextures(material, aiTextureType::aiTextureType_HEIGHT, TextureUsage::Height);
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
        // 4. ambient maps
        LOG("Adding " + std::to_string(AMBIENT_COUNT) + " ambient textures.");
        std::vector<std::shared_ptr<Texture2D>> ambientMaps = loadMaterialTextures(material, aiTextureType::aiTextureType_AMBIENT, TextureUsage::Ambient);
        textures.insert(textures.end(), ambientMaps.begin(), ambientMaps.end());
    }

    LOG(std::string("Returning Meshes ").append(mesh->mName.C_Str()));
    return std::make_shared<Mesh>(vertices, indices, textures, BufferUsage::STATIC_DRAW);
}

std::vector<std::shared_ptr<Texture2D>> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, TextureUsage textureUsage) {
    std::vector<std::shared_ptr<Texture2D>> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        std::string fullPath = m_Directory + "/" + str.C_Str();

        for (const auto& tex: textures_loaded) {
            if(tex->GetPath() == fullPath)
            {
                textures.push_back(tex);
                skip = true;
                break;
            }
        }

        if(!skip) {
            auto texture = std::make_shared<Texture2D>(fullPath, textureUsage);
            textures_loaded.push_back(texture);
            textures.push_back(texture);
        }
    }
    return textures;
}
