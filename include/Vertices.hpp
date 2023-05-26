//
// Created by ianpo on 26/05/2023.
//

#ifndef LEARNOPENGL_VERTICES_HPP
#define LEARNOPENGL_VERTICES_HPP

#include "BufferUsage.hpp"
#include "BufferType.hpp"

class Vertices {
private:
    unsigned int m_BufferId;
    const BufferType m_BufferType;
public:
    Vertices(const void * vertices, unsigned int size, BufferUsage bufferUsage = BufferUsage::STATIC_DRAW);
    ~Vertices();

    void Bind() const;
    void Unbind() const;
};


#endif //LEARNOPENGL_VERTICES_HPP
