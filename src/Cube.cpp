//
// Created by ianpo on 31/05/2023.
//

#include "Cube.hpp"


VertexBufferLayout Vertex::GetLayout() {
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    return layout;
}

Cube::Cube(float size, glm::mat4 model) :
        m_VertexArrayObject(true),
        m_VerticesArray{{{-(size*0.5f), -(size*0.5f), -(size*0.5f)}, {0.0f, 0.0f}}, {{+(size*0.5f), -(size*0.5f), -(size*0.5f)}, {1.0f, 0.0f}}, {{+(size*0.5f), +(size*0.5f), -(size*0.5f)}, {1.0f, 1.0f}}, {{-(size*0.5f), +(size*0.5f), -(size*0.5f)}, {0.0f, 1.0f}}, {{-(size*0.5f), -(size*0.5f), +(size*0.5f)}, {0.0f, 0.0f}}, {{+(size*0.5f), -(size*0.5f), +(size*0.5f)}, {1.0f, 0.0f}}, {{+(size*0.5f), +(size*0.5f), +(size*0.5f)}, {1.0f, 1.0f}}, {{-(size*0.5f), +(size*0.5f), +(size*0.5f)}, {0.0f, 1.0f}}, {{-(size*0.5f), +(size*0.5f), +(size*0.5f)}, {1.0f, 0.0f}}, {{-(size*0.5f), +(size*0.5f), -(size*0.5f)}, {1.0f, 1.0f}}, {{-(size*0.5f), -(size*0.5f), -(size*0.5f)}, {0.0f, 1.0f}}, {{+(size*0.5f), +(size*0.5f), +(size*0.5f)}, {1.0f, 0.0f}}, {{+(size*0.5f), -(size*0.5f), -(size*0.5f)}, {0.0f, 1.0f}}, {{+(size*0.5f), -(size*0.5f), +(size*0.5f)}, {0.0f, 0.0f}}, {{+(size*0.5f), -(size*0.5f), -(size*0.5f)}, {1.0f, 1.0f}}, {{-(size*0.5f), +(size*0.5f), +(size*0.5f)}, {0.0f, 0.0f}}},
        m_IndicesArray{0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4, 8, 9, 10, 10, 4, 8, 11, 2, 12, 12, 13, 11, 10, 14, 5, 5, 4, 10, 3, 2, 11, 11, 15, 3},
        m_Layout(Vertex::GetLayout()),
        m_Vertices((void*)m_VerticesArray, 16 * m_Layout.GetStride(), BufferUsage::STATIC_DRAW),
        m_Indices(m_IndicesArray, 36, BufferUsage::STATIC_DRAW),
        m_Model(model)
{
    m_VertexArrayObject.Bind();
    m_Vertices.Bind();
    m_Indices.Bind();
    m_VertexArrayObject.AddVertex(m_Vertices, m_Layout);
    m_VertexArrayObject.Unbind();
    m_Vertices.Unbind();
    m_Indices.Unbind();
}

void Cube::Bind() const {
    m_VertexArrayObject.Bind();
}

void Cube::Unbind() const {
    m_VertexArrayObject.Unbind();
}

void Cube::Draw() const {
    Bind();
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
