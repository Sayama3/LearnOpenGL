#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "SystemHelper.hpp"
#include "Vertices.hpp"
#include "Indices.hpp"
#include "VertexArrayObject.hpp"


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

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
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
    unsigned int shaderProgram;
    // It's the only variable that will be needed later on.
    // So I keep the rest in its own scope.
    {
        // Vertex Shader
        unsigned int vertexShader;
        {
            std::string vertexShaderSource = SystemHelper::ReadFile("resources/shaders/shader.vert");
            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            const char *cstr = vertexShaderSource.c_str();
            glShaderSource(vertexShader, 1, &cstr, nullptr);
            glCompileShader(vertexShader);
            // Shaders : Checking the successful compilation of the shader.
            int success;
            char infoLog[512];
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
                std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
        }
        // Fragment Shader
        unsigned int fragmentShader;
        {
            std::string fragmentShaderSource = SystemHelper::ReadFile("resources/shaders/shader.frag");
            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            const char *cstr = fragmentShaderSource.c_str();
            glShaderSource(fragmentShader, 1, &cstr, nullptr);
            glCompileShader(fragmentShader);
            // Shaders : Checking the successful compilation of the shader.
            int success;
            char infoLog[512];
            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
                std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
        }
        // Shader Program Bis
        {
            shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram, vertexShader);
            glAttachShader(shaderProgram, fragmentShader);
            glLinkProgram(shaderProgram);
            // Shaders : Checking the successful compilation of the shader program.
            int success;
            char infoLog[512];
            glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
                std::cerr << "ERROR::SHADER::SHADER_PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
        }
        // We now have our ShaderProgram, we don't need the shaders anymore.
        glDeleteShader(fragmentShader);
        glDeleteShader(vertexShader);
    }


   // 1. bind Vertex Array Object
    VertexArrayObject vao;
    vao.Bind();

    // My First Triangle
    // TODO: change this for an array of triangles, that are an alias for 3 vertices1, which are in turn 3 floats.
    //  Just me thinking it would be better, not especially true though.
    float vertices1[] = {
            -0.25f, 0.5f, 0.0f, // top right
            -0.25f, -0.5f, 0.0f, // bottom right
            -0.75f, -0.5f, 0.0f, // bottom left
            -0.75f, 0.5f, 0.0f // top left
    };
    unsigned int indices1[] = { // note that we start from 0!
            0, 1, 3, // first triangle
            1, 2, 3 // second triangle
    };

    // The Vertex Buffer Object.
    // 2.1 copy our vertices1 array in a buffer for OpenGL to use
    Vertices vertices(vertices1, sizeof(vertices1), BufferUsage::STATIC_DRAW);
    vertices.Bind();

    // The Element Buffer Object (st<ore the indices1 of the vertices1)
    // 2.2 copy our indices1 array in a buffer for OpenGL to use
    Indices indices(indices1, sizeof(indices1) / sizeof(indices1[0]), BufferUsage::STATIC_DRAW);
    indices.Bind();

    // 3. then set the vertex attributes pointers
    VertexBufferLayout layout;
    layout.Push<float>(3);
    vao.AddVertex(vertices, layout);

    // You can unbind the VAO afterward so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyway, so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    vao.Unbind();
    vertices.Unbind();
    indices.Unbind();

    // float vertices2[] = {
    //         0.75f, 0.5f, 0.0f, // top right
    //         0.75f, -0.5f, 0.0f, // bottom right
    //         0.25f, -0.5f, 0.0f, // bottom left
    //         0.25f, 0.5f, 0.0f // top left
    // };
    // unsigned int indices2[] = { // note that we start from 0!
    //         0, 1, 3, // first triangle
    //         1, 2, 3 // second triangle
    // };

    // Rendering
    while(!glfwWindowShouldClose(window))
    {
        // Input Processing
        processInput(window);

        //TODO: The rendering/ The renderer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // 4. draw the object
        glUseProgram(shaderProgram);
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
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    // Simple exit with the "escape" button for now.
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}