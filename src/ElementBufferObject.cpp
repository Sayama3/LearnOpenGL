//
// Created by ianpo on 26/05/2023.
//

#include "ElementBufferObject.hpp"

ElementBufferObject::ElementBufferObject(const unsigned int *indices, unsigned int count, BufferUsage bufferUsage) : m_BufferId(), m_BufferType(BufferType::ELEMENT_ARRAY_BUFFER) {
    glGenBuffers(1, &this->m_BufferId);
    glBindBuffer(m_BufferType, m_BufferId);
    glBufferData(m_BufferType, count * sizeof(unsigned int), indices, bufferUsage);
}

ElementBufferObject::~ElementBufferObject() {
    glDeleteBuffers(1, &this->m_BufferId);
}

void ElementBufferObject::Bind() const {
    glBindBuffer(m_BufferType, m_BufferId);
}

void ElementBufferObject::Unbind() const {
    glBindBuffer(m_BufferType, 0);
}
