cmake_minimum_required(VERSION 3.23)

target_sources(OpenGL PRIVATE
        main.cpp
        ElementBufferObject.cpp
        VertexBufferObject.cpp
        VertexArrayObject.cpp
        VertexBufferLayout.cpp
        Shader.cpp
        ShaderProgram.cpp
        Texture2D.cpp
        MathHelper.cpp
        Cube.cpp
        Camera.cpp
        LightSource.cpp
        Logger.cpp
        ImguiContainer.cpp
        )

add_subdirectory(Models)