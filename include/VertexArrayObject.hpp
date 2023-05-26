//
// Created by ianpo on 26/05/2023.
//

#ifndef LEARNOPENGL_VERTEXARRAYOBJECT_HPP
#define LEARNOPENGL_VERTEXARRAYOBJECT_HPP

#include "Vertices.hpp"
#include "VertexBufferLayout.hpp"

class VertexArrayObject {
private:
    unsigned int m_VertexArrayId;
public:
    VertexArrayObject();
    ~VertexArrayObject();

    void Bind() const;
    void Unbind() const;

    void AddVertex(const Vertices & vertices, const VertexBufferLayout & layout);

    inline const unsigned int GetId() const {return m_VertexArrayId;}
};


#endif //LEARNOPENGL_VERTEXARRAYOBJECT_HPP
