//
// Created by ianpo on 31/05/2023.
//

#ifndef LEARNOPENGL_LIGHTSOURCE_HPP
#define LEARNOPENGL_LIGHTSOURCE_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <array>
#include "Indices.hpp"
#include "Vertices.hpp"
#include "VertexArrayObject.hpp"
#include "VertexBufferLayout.hpp"

struct LightSourceVertex {
    glm::vec3 position;
    glm::vec2 uv;
    static VertexBufferLayout GetLayout();
};

class LightSource {
private:

    VertexArrayObject m_VertexArrayObject;
    const LightSourceVertex m_VerticesArray[16];
    const unsigned int m_IndicesArray[36];
    const VertexBufferLayout m_Layout;

    Vertices m_Vertices;
    Indices m_Indices;


public:
    explicit LightSource(float size = 1.0f);
    void Bind() const;
    void Unbind() const;
    void Draw() const;
};


#endif //LEARNOPENGL_LIGHTSOURCE_HPP