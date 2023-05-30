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


    // === Shaders ===
    ShaderProgram shaderProgram(ShaderConstructor("resources/shaders/shader.vert", ShaderType::VERTEX_SHADER),
                                 ShaderConstructor("resources/shaders/shader.frag", ShaderType::FRAGMENT_SHADER));
    shaderProgram.Bind();
    // 1. bind Vertex Array Object
    VertexArrayObject vao;
    vao.Bind();

    // My First Triangle
    // TODO: Change the way we make meshes as this is REALLY unreadable and I make silly mistake when creating a simple square.
    float verticesArray1[] = {
            // Position(3)     // Color(3)       // TexCoord(2)
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
            -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top left
    };
    unsigned int indicesArray1[] = { // note that we start from 0!
            0, 1, 3, // first triangle
            1, 2, 3 // second triangle
    };

    Texture2D texture("resources/textures/container.jpg");
    texture.Unbind();

    // The Vertex Buffer Object.
    // 2.1 copy our verticesArray1 array in a buffer for OpenGL to use
    Vertices vertices(verticesArray1, sizeof(verticesArray1), BufferUsage::STATIC_DRAW);
    vertices.Bind();

    // The Element Buffer Object (st<ore the indicesArray1 of the verticesArray1)
    // 2.2 copy our indicesArray1 array in a buffer for OpenGL to use
    Indices indices(indicesArray1, sizeof(indicesArray1) / sizeof(indicesArray1[0]), BufferUsage::STATIC_DRAW);
    indices.Bind();

    // 3. then set the vertex attributes pointers
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);
    vao.AddVertex(vertices, layout);

    // You can unbind the VAO afterward so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyway, so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    vao.Unbind();
    vertices.Unbind();
    indices.Unbind();
    shaderProgram.Unbind();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 view = glm::mat4(1.0f);
    // note that we’re translating the scene in the reverse direction
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), _width / _height, 0.1f, 100.0f);


    // Rendering
    while(!glfwWindowShouldClose(window))
    {
        // Input Processing
        processInput(window);

        //TODO: The rendering/ The renderer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // 4. draw the object
        texture.Bind();
        shaderProgram.Bind();

        shaderProgram.SetUniform<glm::mat4>("model", model);
        shaderProgram.SetUniform<glm::mat4>("view", view);
        shaderProgram.SetUniform<glm::mat4>("projection", projection);

        vao.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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