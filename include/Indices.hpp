//
// Created by ianpo on 26/05/2023.
//

#ifndef LEARNOPENGL_INDICES_HPP
#define LEARNOPENGL_INDICES_HPP

#include "BufferUsage.hpp"
#include "BufferType.hpp"

class Indices {
private:
    unsigned int m_BufferId;
    const BufferType m_BufferType;
public:
    Indices(const unsigned int *indices, unsigned int count, BufferUsage bufferUsage = BufferUsage::STATIC_DRAW);
    ~Indices();

    void Bind() const;
    void Unbind() const;
};
#endif //LEARNOPENGL_INDICES_HPP
