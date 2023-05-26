//
// Created by ianpo on 26/05/2023.
//

#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram(const std::string& shaderPath1, ShaderType typeShader1) : m_ShaderProgramId(glCreateProgram()) {
    Shader shader1(shaderPath1, typeShader1);
    shader1.CheckCompilation();

    glAttachShader(m_ShaderProgramId, shader1.GetId());
    glLinkProgram(m_ShaderProgramId);
}

ShaderProgram::ShaderProgram(const std::string& shaderPath1, ShaderType typeShader1, const std::string& shaderPath2, ShaderType typeShader2) : m_ShaderProgramId(glCreateProgram()) {
    Shader shader1(shaderPath1, typeShader1);
    shader1.CheckCompilation();
    Shader shader2(shaderPath2, typeShader2);
    shader2.CheckCompilation();

    glAttachShader(m_ShaderProgramId, shader1.GetId());
    glAttachShader(m_ShaderProgramId, shader2.GetId());
    glLinkProgram(m_ShaderProgramId);
}

ShaderProgram::ShaderProgram(const std::string& shaderPath1, ShaderType typeShader1, const std::string& shaderPath2, ShaderType typeShader2, const std::string& shaderPath3, ShaderType typeShader3) : m_ShaderProgramId(glCreateProgram()) {
    Shader shader1(shaderPath1, typeShader1);
    shader1.CheckCompilation();
    Shader shader2(shaderPath2, typeShader2);
    shader2.CheckCompilation();
    Shader shader3(shaderPath3, typeShader3);
    shader3.CheckCompilation();

    glAttachShader(m_ShaderProgramId, shader1.GetId());
    glAttachShader(m_ShaderProgramId, shader2.GetId());
    glAttachShader(m_ShaderProgramId, shader3.GetId());
    glLinkProgram(m_ShaderProgramId);
}

ShaderProgram::ShaderProgram(const Shader &shader1) : m_ShaderProgramId(glCreateProgram())  {
    glAttachShader(m_ShaderProgramId, shader1.GetId());
    glLinkProgram(m_ShaderProgramId);
}

ShaderProgram::ShaderProgram(const Shader &shader1, const Shader &shader2) : m_ShaderProgramId(glCreateProgram())  {
    glAttachShader(m_ShaderProgramId, shader1.GetId());
    glAttachShader(m_ShaderProgramId, shader2.GetId());
    glLinkProgram(m_ShaderProgramId);
}

ShaderProgram::ShaderProgram(const Shader &shader1, const Shader &shader2, const Shader &shader3) : m_ShaderProgramId(glCreateProgram())  {
    glAttachShader(m_ShaderProgramId, shader1.GetId());
    glAttachShader(m_ShaderProgramId, shader2.GetId());
    glAttachShader(m_ShaderProgramId, shader3.GetId());
    glLinkProgram(m_ShaderProgramId);
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(m_ShaderProgramId);

}

void ShaderProgram::Bind() const {
    glUseProgram(m_ShaderProgramId);
}

void ShaderProgram::Unbind() const {
    glUseProgram(0);
}

const unsigned int ShaderProgram::GetId() const {
    return m_ShaderProgramId;
}
