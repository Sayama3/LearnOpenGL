#include <iostream>
#include <glad/glad.h>
#include <GLFW\glfw3.h>
#include <string>
#include "SystemHelper.hpp"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);


int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // My First Triangle
    // TODO: change this for an array of triangles, that are an alias for 3 vertices, which are in turn 3 floats.
    //  Just me thinking it would be better, not especially true though.
    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
    };

    // TODO: From the Vertices, we should be able to create VertexBufferObject. See later on if it's still true.
    // The Vertex Buffer Object.
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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
            } else {
                glUseProgram(shaderProgram);
            }
        }
        // We now have our ShaderProgram, we don't need the shaders anymore.
        glDeleteShader(fragmentShader);
        glDeleteShader(vertexShader);
    }

    // Rendering
    while(!glfwWindowShouldClose(window))
    {
        // Input Processing
        processInput(window);

        //TODO: The rendering/ The renderer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

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