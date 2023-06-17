//
// Created by ianpo on 15/06/2023.
//

#include "Mesh.hpp"
#include <stdio.h>
#include <string.h>
#include "Logger.hpp"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture2D>& textures, BufferUsage usage) :
        m_Vertices(vertices),
        m_Indices(indices),
        m_Textures(textures),
        m_Layout(Vertex::GetVertexBufferLayout()),
        m_VAO(false),
        m_VBO(m_Vertices.data(), m_Vertices.size() * sizeof(Vertex), usage),
        m_EBO(m_Indices.data(), m_Indices.size(), usage)
{
    this->SetupMesh();
    LOG("Create Mesh");
}

void Mesh::SetupMesh() {
    m_VAO.Bind();
    m_VBO.Bind();
    m_EBO.Bind();
    m_VAO.AddVertex(m_VBO, m_Layout);
    m_VAO.Unbind();
    m_VBO.Unbind();
    m_EBO.Unbind();
}

void Mesh::Draw(ShaderProgram &shader) {
    int textureTypes[TextureUsage::Count];
    memset(textureTypes, 0, sizeof(textureTypes));

    for (int i = 0; i < m_Textures.size(); ++i) {
        m_Textures[i].Bind(static_cast<unsigned int>(i));
        std::string uniformName = "material.";
        uniformName.append(TextureUsageToName(m_Textures[i].m_TextureUsage));
        uniformName.append(std::to_string(textureTypes[m_Textures[i].m_TextureUsage]++));

        shader.SetUniform(uniformName, i);
    }

    m_VAO.Bind();
    m_EBO.Draw(GLDrawMode::TRIANGLES);
    m_VAO.Unbind();

    glActiveTexture(TextureSlot::TEXTURE0);
}

Mesh::~Mesh() {
    LOG("Destroy Mesh");
}
