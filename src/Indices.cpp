//
// Created by ianpo on 26/05/2023.
//

#include "Indices.hpp"

Indices::Indices(const unsigned int *indices, unsigned int count, BufferUsage bufferUsage) : m_BufferId(), m_BufferType(BufferType::ELEMENT_ARRAY_BUFFER) {
    glGenBuffers(1, &this->m_BufferId);
    glBindBuffer(m_BufferType, m_BufferId);
    glBufferData(m_BufferType, count * sizeof(unsigned int), indices, bufferUsage);
}

Indices::~Indices() {
    glDeleteBuffers(1, &this->m_BufferId);
}

void Indices::Bind() const {
    glBindBuffer(m_BufferType, m_BufferId);
}

void Indices::Unbind() const {
    glBindBuffer(m_BufferType, 0);
}
