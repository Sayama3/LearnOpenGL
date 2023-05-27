//
// Created by ianpo on 26/05/2023.
//

#ifndef LEARNOPENGL_SHADERPROGRAM_HPP
#define LEARNOPENGL_SHADERPROGRAM_HPP

#include "Shader.hpp"
#include "vector"



// TODO: Change the class to use Template instead of copy pasting the Shader Path & Type
class ShaderProgram {
private:
    unsigned int m_ShaderProgramId;
    void AttachShader(unsigned int shaderId);
    void AttachShader(const Shader & shader);
    void Link();
public:
    ShaderProgram(ShaderConstructor shader1);
    ShaderProgram(ShaderConstructor shader1, ShaderConstructor shader2);
    ShaderProgram(ShaderConstructor shader1, ShaderConstructor shader2, ShaderConstructor shader3);
    ShaderProgram(const std::vector<ShaderConstructor> & shaders);
    ShaderProgram(const Shader &shader1);
    ShaderProgram(const Shader &shader1, const Shader & shader2);
    ShaderProgram(const Shader &shader1, const Shader & shader2, const Shader & shader3);
    ShaderProgram(const std::vector<Shader> & shaders);

    ~ShaderProgram();

    void Bind() const;
    void Unbind() const;
    unsigned int GetId() const;
};


#endif //LEARNOPENGL_SHADERPROGRAM_HPP
