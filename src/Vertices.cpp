//
// Created by ianpo on 26/05/2023.
//

#include "Vertices.hpp"

Vertices::Vertices(const void *vertices, unsigned int size, BufferUsage bufferUsage) : m_BufferId() , m_BufferType(BufferType::ARRAY_BUFFER){
    glGenBuffers(1, &this->m_BufferId);
    glBindBuffer(m_BufferType, m_BufferId);
    glBufferData(m_BufferType, size, vertices, bufferUsage);
}

Vertices::~Vertices() {
    glDeleteBuffers(1, &this->m_BufferId);
}

void Vertices::Bind() const {
    glBindBuffer(m_BufferType, m_BufferId);
}

void Vertices::Unbind() const {
    glBindBuffer(m_BufferType, 0);
}
