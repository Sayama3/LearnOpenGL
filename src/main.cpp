#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <string>
#include "SystemHelper.hpp"
#include "Vertices.hpp"
#include "Indices.hpp"
#include "VertexArrayObject.hpp"
#include "ShaderProgram.hpp"
#include "Texture2D.hpp"
#include "MathHelper.hpp"
#include "Cube.hpp"
float _width = 800;
float _height = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);


int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(_width, _height, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);


    // === Shaders ===
    ShaderProgram shaderProgram(ShaderConstructor("resources/shaders/shader.vert", ShaderType::VERTEX_SHADER),
                                 ShaderConstructor("resources/shaders/shader.frag", ShaderType::FRAGMENT_SHADER));
    shaderProgram.Bind();

    Texture2D texture("resources/textures/container.jpg");
    texture.Unbind();

    Cube cube;

    shaderProgram.Unbind();

//    cube.m_Model = glm::rotate(cube.m_Model, glm::radians(-55.0f), glm::vec3(1.0f, 1.0f, 1.0f));

    glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f, 0.0f, 0.0f),
    glm::vec3( 2.0f, 5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f, 3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f, 2.0f, -2.5f),
    glm::vec3( 1.5f, 0.2f, -1.5f),
    glm::vec3(-1.3f, 1.0f, -1.5f)
    };
    float rotationSpeed = 5.0f;
    // Rendering
    while(!glfwWindowShouldClose(window))
    {
        // Input Processing
        processInput(window);

        //TODO: The rendering/ The renderer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = glm::mat4(1.0f);
        // note that we’re translating the scene in the reverse direction
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(60.0f), _width / _height, 0.1f, 100.0f);

        // 4. draw the object
        texture.Bind();
        shaderProgram.Bind();

        shaderProgram.SetUniform<glm::mat4>("view", view);
        shaderProgram.SetUniform<glm::mat4>("projection", projection);

        for(unsigned int i = 0; i < 10; i++) {
            auto& pos = cubePositions[i];
            glm::mat4 model = glm::identity<glm::mat4>();
            model = glm::translate(model, pos);
            float angle = 20.0f * i;
            if(i%3 == 0){
                angle += static_cast<float>(glfwGetTime()) * rotationSpeed * (i%6 ? -1.0f : 1.0f);
            }
            model = glm::rotate(model, glm::radians(angle),glm::vec3(1.0f, 0.3f, 0.5f));
            shaderProgram.SetUniform<glm::mat4>("model", model);
            cube.Draw();
        }

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    _width = width;
    _height = height;
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    // Simple exit with the "escape" button for now.
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}