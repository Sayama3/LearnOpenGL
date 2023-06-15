//
// Created by ianpo on 15/06/2023.
//

#ifndef LEARNOPENGL_MESH_HPP
#define LEARNOPENGL_MESH_HPP

#include <vector>
#include "Vertex.hpp"
#include "Texture2D.hpp"
#include "VertexArrayObject.hpp"
#include "VertexBufferLayout.hpp"
#include "VertexBufferObject.hpp"
#include "ElementBufferObject.hpp"

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture2D> textures;
private:
    VertexArrayObject vao;
    VertexBufferObject vbo;
    ElementBufferObject ebo;
};


#endif //LEARNOPENGL_MESH_HPP
