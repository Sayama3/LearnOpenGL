#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <glm/gtx/string_cast.hpp>
#include "SystemHelper.hpp"
#include "Vertices.hpp"
#include "Indices.hpp"
#include "VertexArrayObject.hpp"
#include "ShaderProgram.hpp"
#include "Texture2D.hpp"
#include "MathHelper.hpp"
#include "Cube.hpp"
#include "Camera.hpp"
#include "GLFWType.hpp"
#include "LightSource.hpp"

float _width = 800;
float _height = 600;

bool cursorEnable = true;

Camera camera({_width, _height}, {0,0,3});

// Set this in the renderer.
double currentFrame = 0.0;
double deltaTime = 0.001667; // Arbitrary 60fps
double lastFrame = 0.0;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    cursorEnable = false;
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);

    // === Light ===
    LightSource lightSource;
    ShaderProgram lightSourceShader(ShaderConstructor("resources/shaders/lightsource.vert", ShaderType::VERTEX_SHADER),
                             ShaderConstructor("resources/shaders/lightsource.frag", ShaderType::FRAGMENT_SHADER));
    lightSourceShader.Bind();
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);


    // === Shaders ===
    ShaderProgram cubeShader(ShaderConstructor("resources/shaders/container.vert", ShaderType::VERTEX_SHADER),
                             ShaderConstructor("resources/shaders/container.frag", ShaderType::FRAGMENT_SHADER));
    cubeShader.Bind();
    cubeShader.SetUniform<glm::vec3>("objectColor", {1.0f, 0.5f, 0.31f});
    cubeShader.SetUniform<glm::vec3>("lightColor", {1.0f, 1.0f, 1.0f});

    Texture2D texture("resources/textures/container.jpg");
    texture.Unbind();

    // === Models ===
    Cube cube;

    cubeShader.Unbind();

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
    glm::vec3(-1.3f, 1.0f, -1.5f),
    };
    float rotationSpeed = 5.0f;

    // === Rendering ===
    while(!glfwWindowShouldClose(window))
    {
        // Frame duration processing.
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Input Processing
        processInput(window);

        // Clearing old image.
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Rendering LightSource
        {
            lightSourceShader.Bind();
            auto model = glm::mat4(1.0f);
            model = glm::translate(model, lightPos);
            model = glm::scale(model, glm::vec3(0.2f));
            lightSourceShader.SetUniform<glm::mat4>("model", model);
            lightSourceShader.SetUniform<glm::mat4>("view", camera.GetViewMatrix());
            lightSourceShader.SetUniform<glm::mat4>("projection", camera.GetProjectionMatrix());
            lightSource.Bind();
            lightSource.Draw();
            lightSourceShader.Unbind();
        }

        // Rendering meshes.
        {
            // Texture Update
            texture.Bind();
            cubeShader.Bind();

            // Updating projection & view matrix.
            cubeShader.SetUniform<glm::mat4>("view", camera.GetViewMatrix());
            cubeShader.SetUniform<glm::mat4>("projection", camera.GetProjectionMatrix());
            cubeShader.SetUniform<glm::vec3>("lightPos", lightPos);
            cubeShader.SetUniform<glm::vec3>("viewPos", camera.GetPosition());
            for (unsigned int i = 0; i < sizeof(cubePositions) / sizeof(cubePositions[0]); i++) {
                auto &pos = cubePositions[i];
                auto model = glm::identity<glm::mat4>();
                model = glm::translate(model, pos);
                 float angle = 20.0f * i;
                 if (i % 3 == 0) {
                     angle += static_cast<float>(glfwGetTime()) * rotationSpeed * (i % 6 ? -1.0f : 1.0f);
                 }
                 model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                cubeShader.SetUniform<glm::mat4>("model", model);
                cube.Draw();
            }
            texture.Unbind();
            cubeShader.Unbind();
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
    camera.OnScreenSizeChange({width, height});
}
bool hasPressCtrl = false;
void processInput(GLFWwindow *window)
{
    // Simple exit with the "escape" button for now.
    if(glfwGetKey(window, GLFWKey::KEY_ESCAPE) == GLFWKeyState::PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    if(glfwGetKey(window, GLFWKey::KEY_LEFT_CONTROL) == GLFWKeyState::PRESS && !hasPressCtrl)
    {
        hasPressCtrl = !hasPressCtrl;
        if(cursorEnable) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        cursorEnable = !cursorEnable;
    } else if(glfwGetKey(window, GLFWKey::KEY_LEFT_CONTROL) == GLFWKeyState::RELEASE && hasPressCtrl) {
        hasPressCtrl = !hasPressCtrl;
    }

    camera.ProcessKeyboard(window, deltaTime);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if(!cursorEnable) {
        camera.ProcessMouseCursor({xpos, ypos});
    }
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if(!cursorEnable) {
        camera.ProcessMouseScroll({xoffset, yoffset});
    }
}