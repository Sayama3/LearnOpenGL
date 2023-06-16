//
// Created by ianpo on 16/06/2023.
//

#include "Model.hpp"
#include <iostream>

Model::Model(const std::string &path) : m_Meshes(), m_Directory(path.substr(0, path.find_last_of('/'))) {
    this->loadModel(path);
}

void Model::Draw(ShaderProgram &shader) {
    for (auto& mesh : m_Meshes) {
        mesh.Draw(shader);
    }
}

void Model::loadModel(const std::string &path) {
    // Create an instance of the Importer class
    Assimp::Importer importer;

    // And have it read the given file with some example postprocessing
    // Usually - if speed is not the most important aspect for you - you'll
    // probably to request more postprocessing than we do in this example.
    const aiScene* scene = importer.ReadFile( path,
//                                              aiProcess_CalcTangentSpace        |
                                              aiProcess_Triangulate             |
                                              aiProcess_JoinIdenticalVertices   |
                                              aiProcess_GenNormals   |
                                              aiProcess_FlipUVs                 |
                                              aiProcess_SortByPType);

    // If the import failed, report it
    if (nullptr == scene) {
        std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    m_Meshes.reserve(scene->mNumMeshes);

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
    for (int i = 0; i < node->mNumMeshes; ++i) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_Meshes.push_back(processMesh(mesh, scene));
    }

    for (int i = 0; i < node->mNumChildren; ++i) {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertices;
    vertices.reserve(mesh->mNumVertices);
    std::vector<unsigned int> indices;
    indices.reserve(mesh->mNumFaces * 3);
    std::vector<Texture2D> textures;

    // Process Vertex
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
    for (int i = 0; i < mesh->mNumFaces; ++i) {
        auto& face = mesh->mFaces[i];
        for (int j = 0; j < face.mNumIndices; ++j) {
            indices.push_back(face.mIndices[j]);
        }
    }

    //process materials
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial *mat = scene->mMaterials[mesh->mMaterialIndex];

        auto diffuseCount = mat->GetTextureCount(aiTextureType_DIFFUSE);
        auto specularCount = mat->GetTextureCount(aiTextureType_SPECULAR);

        textures.reserve(diffuseCount + specularCount);

        std::vector<Texture2D> diffuseMaps = loadMaterialTextures(mat, aiTextureType_DIFFUSE, TextureUsage::Diffuse);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<Texture2D> specularMaps = loadMaterialTextures(mat, aiTextureType_SPECULAR, TextureUsage::Specular);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh(vertices, indices, textures);
}

std::vector<Texture2D> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, TextureUsage textureUsage) {
    std::vector<Texture2D> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;

        for (const auto& tex: textures_loaded) {
            if(std::strcmp(tex.GetPath().data(), str.C_Str()) == 0)
            {
                textures.push_back(tex);
                skip = true;
                break;
            }
        }

        if(!skip) {
            Texture2D texture(str.C_Str(), textureUsage);
            textures.push_back(texture);
            textures_loaded.push_back(texture);
        }


    }
    return textures;
}
