cmake_minimum_required(VERSION 3.23)

target_sources(OpenGL PRIVATE
        glad.c
        main.cpp
        Indices.cpp
        Vertices.cpp
        )