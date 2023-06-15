//
// Created by ianpo on 15/06/2023.
//

#ifndef LEARNOPENGL_VERTEX_HPP
#define LEARNOPENGL_VERTEX_HPP

#include "glm/glm.hpp"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

#endif //LEARNOPENGL_VERTEX_HPP
