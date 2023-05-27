//
// Created by ianpo on 27/05/2023.
//

#ifndef LEARNOPENGL_OPENGLTYPE_HPP
#define LEARNOPENGL_OPENGLTYPE_HPP

#include <glad/glad.h>

enum GLType {
    /**
     * Accepted by:\n\n
     * - glVertexAttribPointer\\nn
     * - glVertexAttribIPointer\n\n
     */
    BYTE = GL_BYTE,
    /**
     * Accepted by:\n
     * - glVertexAttribPointer\n
     * - glVertexAttribIPointer\n
     */
    UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
    /**
     * Accepted by:\n
     * - glVertexAttribPointer\n
     * - glVertexAttribIPointer\n
     */
    SHORT = GL_SHORT,
    /**
     * Accepted by:\n
     * - glVertexAttribPointer\n
     * - glVertexAttribIPointer\n
     */
    UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
    /**
     * Accepted by:\n
     * - glVertexAttribPointer\n
     * - glVertexAttribIPointer\n
     */
    INT = GL_INT,
    /**
     * Accepted by:\n
     * - glVertexAttribPointer\n
     * - glVertexAttribIPointer\n
     */
    UNSIGNED_INT = GL_UNSIGNED_INT,
    /**
     * Accepted by:\n
     * - glVertexAttribPointer\n
     * - glVertexAttribIPointer\n
     */
    HALF_FLOAT = GL_HALF_FLOAT,
    /**
     * Accepted by:\n
     * - glVertexAttribPointer\n
     */
    FLOAT = GL_FLOAT,
    /**
     * Accepted by:\n
     * - glVertexAttribPointer\n
     * - glVertexAttribLPointer\n
     */
    DOUBLE = GL_DOUBLE,
    /**
     * Accepted by:\n
     * - glVertexAttribPointer\n
     */
    FIXED = GL_FIXED,
    /**
     * Accepted by:\n
     * - glVertexAttribPointer\n
     */
    INT_2_10_10_10_REV = GL_INT_2_10_10_10_REV,
    /**
     * Accepted by:\n
     * - glVertexAttribPointer\n
     */
    UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV,
    /**
     * Accepted by:\n
     * - glVertexAttribPointer\n
     */
    UNSIGNED_INT_10F_11F_11F_REV = GL_UNSIGNED_INT_10F_11F_11F_REV,
};

#endif //LEARNOPENGL_OPENGLTYPE_HPP
