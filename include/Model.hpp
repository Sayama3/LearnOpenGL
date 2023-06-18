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
#include "MathHelper.hpp"
#include <memory>

// TODO: Have a hierarchy and a node system so that we can easily navigate and draw it.
class Model {
public:
    Model(const std::string& path, glm::mat4 model = glm::identity<glm::mat4>());
    Model (const Model&) = delete;
    Model& operator= (const Model&) = delete;
    void Draw(ShaderProgram& shader);
private:
    std::vector<std::shared_ptr<Mesh>> m_Meshes;
    std::string m_Directory;
    std::vector<std::shared_ptr<Texture2D>> textures_loaded;
    // In private for now as the change won't influence the sub-meshes.
    glm::mat4 m_Model;
    void loadModel(const std::string& path);
    void processNode(aiNode *node, const aiScene *scene, const glm::mat4& parentMatrix);
    std::shared_ptr<Mesh> processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<std::shared_ptr<Texture2D>> loadMaterialTextures(aiMaterial *mat, aiTextureType type, TextureUsage textureUsage);
};


#endif //LEARNOPENGL_MODEL_HPP
