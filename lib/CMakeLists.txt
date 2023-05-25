cmake_minimum_required(VERSION 3.24)
project(LearnOpenGL)

add_subdirectory(glfw)
target_link_libraries(OpenGL PUBLIC glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(OpenGL PUBLIC OpenGL::GL)

add_subdirectory(glm)
target_link_libraries(OpenGL PUBLIC glm)