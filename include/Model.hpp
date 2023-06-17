//
// Created by ianpo on 16/06/2023.
//

#ifndef LEARNOPENGL_MODEL_HPP
#define LEARNOPENGL_MODEL_HPP

#include <string>
#include <vector>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include "Mesh.hpp"
#include "Texture2D.hpp"
#include "ShaderProgram.hpp"
#include <memory>

class Model {
public:
    Model(const std::string& path);
    void Draw(ShaderProgram& shader);
private:
    std::vector<std::shared_ptr<Mesh>> m_Meshes;
    std::string m_Directory;
    std::vector<std::shared_ptr<Texture2D>> textures_loaded;
    void loadModel(const std::string& path);
    void processNode(aiNode *node, const aiScene *scene);
    std::shared_ptr<Mesh> processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<std::shared_ptr<Texture2D>> loadMaterialTextures(aiMaterial *mat, aiTextureType type, TextureUsage textureUsage);
};


#endif //LEARNOPENGL_MODEL_HPP
