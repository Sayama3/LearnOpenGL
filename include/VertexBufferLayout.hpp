//
// Created by ianpo on 26/05/2023.
//

#ifndef LEARNOPENGL_VERTEXBUFFERLAYOUT_HPP
#define LEARNOPENGL_VERTEXBUFFERLAYOUT_HPP

#include <vector>
#include <stdexcept>
#include "glad/glad.h"
#include "OpenGLType.hpp"


struct VertexBufferElement {
    GLType type;
    int count;
    bool normalized;

    inline unsigned int GetSizeOfType() const { return GetSizeOfType(type); }

    static unsigned int GetSizeOfType(enum GLType type);
};

class VertexBufferLayout {
private:
    unsigned int m_Stride;
    std::vector<VertexBufferElement> m_Elements;
public:
    VertexBufferLayout();

    template<typename T>
    inline void Push(int count) {
        throw std::runtime_error("Type not implemented.");
    }

    inline const std::vector<VertexBufferElement> &GetElements() const { return m_Elements; }

    inline unsigned int GetStride() const { return m_Stride; }
};

template<>
void VertexBufferLayout::Push<float>(int count);

template<>
void VertexBufferLayout::Push<unsigned int>(int count);

template<>
void VertexBufferLayout::Push<int>(int count);

template<>
void VertexBufferLayout::Push<unsigned char>(int count);

template<>
void VertexBufferLayout::Push<char>(int count);



#endif //LEARNOPENGL_VERTEXBUFFERLAYOUT_HPP
