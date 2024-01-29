//
// Created by Matej on 29/12/2023.
//

#include "window.h"

#include <stdexcept>
#include <glad/glad.h>

using namespace minecraft;

Window::Window(const char* title, i32 width, i32 height)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    m_width = width;
    m_height = height;
    m_handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!m_handle)
        spdlog::critical("Failed to create GLFW window");

    glfwMakeContextCurrent(m_handle);
    spdlog::debug("Created window ({}x{})", width, height);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        spdlog::critical("Failed to initialize GLAD (OpenGL)");

    spdlog::info("Vendor:   {}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
    spdlog::info("Renderer: {}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
    spdlog::info("Version:  {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));

    glfwSwapInterval(1);
}

Window::~Window()
{
    glfwTerminate();
}
