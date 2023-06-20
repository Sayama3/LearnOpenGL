//
// Created by Iannis on 6/20/2023.
//

#ifndef LEARNOPENGL_IMGUICONTAINER_HPP
#define LEARNOPENGL_IMGUICONTAINER_HPP

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class ImguiContainer {
private:
    ImGuiIO * io;
public:
    ImguiContainer(GLFWwindow* window, const char* glsl_version);
    ~ImguiContainer();

    ImguiContainer (const ImguiContainer&) = delete;
    ImguiContainer& operator= (const ImguiContainer&) = delete;

    void BeginFrame() const;
    void EndFrame() const;
    const ImGuiIO * GetImGui() const;
};


#endif //LEARNOPENGL_IMGUICONTAINER_HPP
