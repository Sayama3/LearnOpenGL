//
// Created by Iannis on 30/05/2023.
//

#include "MathHelper.hpp"

namespace MathHelper {
    // TODO: Do better.
    glm::mat4 RotationMatrix(glm::vec3 axis, float angleInDegree) {
        auto mat = glm::mat4(1.0f);
        return glm::rotate(mat, glm::radians(angleInDegree), axis);
    }
} // MathHelper