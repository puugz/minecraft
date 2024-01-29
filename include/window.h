//
// Created by Matej on 29/12/2023.
//

#pragma once

#include "common.h"

namespace minecraft
{
    enum class CursorMode
    {
        Normal = GLFW_CURSOR_NORMAL,
        Hidden = GLFW_CURSOR_HIDDEN,
        Disabled = GLFW_CURSOR_DISABLED,
    };

    class Window {
    public:
        Window(const char* title, i32 width, i32 height);
        ~Window();

        void cursor_mode(CursorMode mode) const
        {
            glfwSetInputMode(m_handle, GLFW_CURSOR, static_cast<i32>(mode));
        }

        GLFWwindow* handle() const { return m_handle; }

        i32 width() const { return m_width; }
        i32 height() const { return m_height; }

        void queue_close() const { glfwSetWindowShouldClose(m_handle, true); }

        bool should_close() const { return glfwWindowShouldClose(m_handle); }

        void swap_buffers() const { glfwSwapBuffers(m_handle); }
        void poll_events() const { glfwPollEvents(); }

    private:
        GLFWwindow* m_handle;
        i32 m_width, m_height;
    };
}
