//
// Created by ianpo on 26/05/2023.
//

#include "VertexBufferLayout.hpp"
VertexBufferLayout::VertexBufferLayout() : m_Stride(0) {}

unsigned int VertexBufferElement::GetSizeOfType(enum GLType type) {
    switch (type) {
        case BYTE:
            return sizeof(GLbyte);
        case UNSIGNED_BYTE:
            return sizeof(GLuint);
        case SHORT:
            return sizeof(GLshort);
        case UNSIGNED_SHORT:
            return sizeof(GLushort);
        case INT:
            return sizeof(GLint);
        case UNSIGNED_INT:
            return sizeof(GLuint);
        case HALF_FLOAT:
            return sizeof(GLhalf);
        case FLOAT:
            return sizeof(GLfloat);
        case DOUBLE:
            return sizeof(GLdouble);
        case FIXED:
            return sizeof(GLfixed);
        default:
            throw std::runtime_error("Type not implemented.");
    }
}

template<>
void VertexBufferLayout::Push<float>(int count) {
    m_Elements.push_back({GLType::FLOAT, count, false});
    m_Stride += VertexBufferElement::GetSizeOfType(GLType::FLOAT) * count;
}

template<>
void VertexBufferLayout::Push<unsigned int>(int count) {
    m_Elements.push_back({GLType::UNSIGNED_INT, count, false});
    m_Stride += VertexBufferElement::GetSizeOfType(GLType::UNSIGNED_INT) * count;
}

template<>
void VertexBufferLayout::Push<int>(int count) {
    m_Elements.push_back({GLType::INT, count, false});
    m_Stride += VertexBufferElement::GetSizeOfType(GLType::INT) * count;
}

template<>
void VertexBufferLayout::Push<unsigned char>(int count) {
    m_Elements.push_back({GLType::UNSIGNED_BYTE, count, true});
    m_Stride += VertexBufferElement::GetSizeOfType(GLType::UNSIGNED_BYTE) * count;
}

template<>
void VertexBufferLayout::Push<char>(int count) {
    m_Elements.push_back({GLType::BYTE, count, true});
    m_Stride += VertexBufferElement::GetSizeOfType(GLType::BYTE) * count;
}
