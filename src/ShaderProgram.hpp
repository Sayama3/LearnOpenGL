//
// Created by ianpo on 26/05/2023.
//

#ifndef LEARNOPENGL_SHADERPROGRAM_HPP
#define LEARNOPENGL_SHADERPROGRAM_HPP

#include "Shader.hpp"

// TODO: Change the class to use Template instead of copy pasting the Shader Path & Type
class ShaderProgram {
private:
    unsigned int m_ShaderProgramId;
public:
    ShaderProgram(const std::string& shaderPath1, ShaderType typeShader1);
    ShaderProgram(const std::string& shaderPath1, ShaderType typeShader1, const std::string& shaderPath2, ShaderType typeShader2);
    ShaderProgram(const std::string& shaderPath1, ShaderType typeShader1, const std::string& shaderPath2, ShaderType typeShader2, const std::string& shaderPath3, ShaderType typeShader3);
    ShaderProgram(const Shader &shader1);
    ShaderProgram(const Shader &shader1, const Shader & shader2);
    ShaderProgram(const Shader &shader1, const Shader & shader2, const Shader & shader3);

    ~ShaderProgram();

    void Bind() const;
    void Unbind() const;
    const unsigned int GetId() const;
};


#endif //LEARNOPENGL_SHADERPROGRAM_HPP
