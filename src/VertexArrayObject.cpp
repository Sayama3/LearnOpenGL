//
// Created by ianpo on 26/05/2023.
//

#include "VertexArrayObject.hpp"
#include "glad/glad.h"

VertexArrayObject::VertexArrayObject(bool shouldBind) : m_VertexArrayId(){
    glGenVertexArrays(1, &this->m_VertexArrayId);
    if(shouldBind) {
        Bind();
    }
}

VertexArrayObject::~VertexArrayObject() {
    glDeleteVertexArrays(1, &this->m_VertexArrayId);
}

void VertexArrayObject::Bind() const {
    glBindVertexArray(this->m_VertexArrayId);
}

void VertexArrayObject::Unbind() const {
    glBindVertexArray(0);
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-void-pointer-cast"
void VertexArrayObject::AddVertex(const VertexBufferObject & vertices, const VertexBufferLayout & layout) {
    Bind();
    vertices.Bind();

    const auto &elements = layout.GetElements();
    unsigned int offset = 0;
    for (int i = 0; i < elements.size(); ++i) {
        auto &element = elements[i];
        glVertexAttribPointer(i, element.count, element.type, element.normalized, static_cast<GLsizei>(layout.GetStride()), (const void *) offset);
        glEnableVertexAttribArray(i);
        offset += element.count * element.GetSizeOfType();
    }
}
#pragma clang diagnostic pop


