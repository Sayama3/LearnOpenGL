//
// Created by ianpo on 26/05/2023.
//

#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram(const Shader &shader1) : m_ShaderProgramId(glCreateProgram())  {
    AttachShader(shader1);

    Link();
}

ShaderProgram::ShaderProgram(const Shader &shader1, const Shader &shader2) : m_ShaderProgramId(glCreateProgram())  {
    AttachShader(shader1);
    AttachShader(shader2);

    Link();
}

ShaderProgram::ShaderProgram(const Shader &shader1, const Shader &shader2, const Shader &shader3) : m_ShaderProgramId(glCreateProgram())  {
    AttachShader(shader1);
    AttachShader(shader2);
    AttachShader(shader3);

    Link();
}

ShaderProgram::ShaderProgram(const std::vector<ShaderConstructor> &shaders) : m_ShaderProgramId(glCreateProgram()) {
    auto shadersCount = shaders.size();
    std::vector<Shader> instances;
    instances.reserve(shadersCount);
    for (int i = 0; i < shadersCount; ++i) {
        instances.push_back(shaders[i].CreateShader());
        instances[i].CheckCompilation();
        AttachShader(instances[i]);
    }
    Link();
}

ShaderProgram::ShaderProgram(const std::vector<Shader> &shaders) : m_ShaderProgramId(glCreateProgram())  {
    for (const auto& shader: shaders) {
        shader.CheckCompilation();
        AttachShader(shader);
    }
    Link();
}

ShaderProgram::ShaderProgram(ShaderConstructor shader1) : m_ShaderProgramId(glCreateProgram()) {
    auto instance1 = shader1.CreateShader();
    instance1.CheckCompilation();
    AttachShader(instance1);

    Link();
}

ShaderProgram::ShaderProgram(ShaderConstructor shader1, ShaderConstructor shader2) : m_ShaderProgramId(glCreateProgram()) {
    auto instance1 = shader1.CreateShader();
    instance1.CheckCompilation();
    AttachShader(instance1);

    auto instance2 = shader2.CreateShader();
    instance2.CheckCompilation();
    AttachShader(instance2);

    Link();
}

ShaderProgram::ShaderProgram(ShaderConstructor shader1, ShaderConstructor shader2, ShaderConstructor shader3) : m_ShaderProgramId(glCreateProgram()) {
    auto instance1 = shader1.CreateShader();
    instance1.CheckCompilation();
    AttachShader(instance1);

    auto instance2 = shader2.CreateShader();
    instance2.CheckCompilation();
    AttachShader(instance2);

    auto instance3 = shader3.CreateShader();
    instance3.CheckCompilation();
    AttachShader(instance3);

    Link();
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

unsigned int ShaderProgram::GetId() const {
    return m_ShaderProgramId;
}

void ShaderProgram::AttachShader(unsigned int shaderId) {
    glAttachShader(m_ShaderProgramId, shaderId);
}

void ShaderProgram::AttachShader(const Shader &shader) {
    glAttachShader(m_ShaderProgramId, shader.GetId());
}


void ShaderProgram::Link() {
    glLinkProgram(m_ShaderProgramId);
}

