cmake_minimum_required(VERSION 3.23)

target_sources(OpenGL PRIVATE
        glad.c
        main.cpp
        Indices.cpp
        Vertices.cpp
        VertexArrayObject.cpp
        VertexBufferLayout.cpp
        Shader.cpp
        ShaderProgram.cpp
        Texture2D.cpp
        )