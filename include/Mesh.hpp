//
// Created by ianpo on 15/06/2023.
//

#ifndef LEARNOPENGL_MESH_HPP
#define LEARNOPENGL_MESH_HPP

#include <vector>
#include "Vertex.hpp"
#include "Texture2D.hpp"
#include "VertexArrayObject.hpp"
#include "VertexBufferObject.hpp"
#include "ElementBufferObject.hpp"
#include "VertexBufferLayout.hpp"
#include "ShaderProgram.hpp"

class Mesh {
public:
    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices;
    std::vector<Texture2D> m_Textures;

    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture2D>& textures, BufferUsage usage = BufferUsage::STATIC_DRAW);
    void Draw(ShaderProgram& shader);

private:
    VertexBufferLayout m_Layout;
    VertexArrayObject m_VAO;
    VertexBufferObject m_VBO;
    ElementBufferObject m_EBO;

    void SetupMesh();
};


#endif //LEARNOPENGL_MESH_HPP
