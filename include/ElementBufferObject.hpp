//
// Created by ianpo on 26/05/2023.
//

#ifndef LEARNOPENGL_ELEMENTBUFFEROBJECT_HPP
#define LEARNOPENGL_ELEMENTBUFFEROBJECT_HPP

#include "BufferUsage.hpp"
#include "BufferType.hpp"

class ElementBufferObject {
private:
    unsigned int m_BufferId;
    const BufferType m_BufferType;
public:
    ElementBufferObject(const unsigned int *indices, unsigned int count, BufferUsage bufferUsage = BufferUsage::STATIC_DRAW);
    ~ElementBufferObject();

    void Bind() const;
    void Unbind() const;
};
#endif //LEARNOPENGL_ELEMENTBUFFEROBJECT_HPP
