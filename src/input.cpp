//
// Created by Matej on 29/12/2023.
//

#include "input.h"

#include "app.h"
#include "common.h"

using namespace minecraft;

namespace
{
    Input::State state;
}

void App::update_input() const
{
    for (i32 i = 0; i <= GLFW_KEY_LAST; ++i)
    {
        state.keys[i].pressed = false;
        state.keys[i].released = false;

        if (glfwGetKey(m_window.handle(), i) == GLFW_PRESS)
        {
            if (!state.keys[i].down)
                state.keys[i].pressed = true;
            state.keys[i].down = true;
        }
        else
        {
            if (state.keys[i].down)
                state.keys[i].released = true;
            state.keys[i].down = false;
        }
    }

    // Update mouse button states
    for (i32 i = 0; i <= GLFW_MOUSE_BUTTON_LAST; ++i)
    {
        state.mouse[i].pressed = false;
        state.mouse[i].released = false;

        if (glfwGetMouseButton(m_window.handle(), i) == GLFW_PRESS)
        {
            if (!state.mouse[i].down)
                state.mouse[i].pressed = true;
            state.mouse[i].down = true;
        }
        else
        {
            if (state.mouse[i].down)
                state.mouse[i].released = true;
            state.mouse[i].down = false;
        }
    }
}

bool Input::ctrl()
{
    return down(Key::LeftControl) || down(Key::RightControl);
}

bool Input::shift()
{
    return down(Key::LeftShift) || down(Key::RightShift);
}

bool Input::alt()
{
    return down(Key::LeftAlt) || down(Key::RightAlt);
}

bool Input::super()
{
    return down(Key::LeftSuper) || down(Key::RightSuper);
}

bool Input::pressed(Key key)
{
    const auto index = static_cast<i32>(key);
    return index >= 0 && index < GLFW_KEY_LAST && state.keys[index].pressed;
}

bool Input::down(Key key)
{
    const auto index = static_cast<i32>(key);
    return index >= 0 && index < GLFW_KEY_LAST && state.keys[index].down;
}

bool Input::released(Key key)
{
    const auto index = static_cast<i32>(key);
    return index >= 0 && index < GLFW_KEY_LAST && state.keys[index].released;
}

bool Input::pressed(MouseButton btn)
{
    const auto index = static_cast<i32>(btn);
    return index >= 0 && index < GLFW_MOUSE_BUTTON_LAST && state.mouse[index].pressed;
}

bool Input::down(MouseButton btn)
{
    const auto index = static_cast<i32>(btn);
    return index >= 0 && index < GLFW_MOUSE_BUTTON_LAST && state.mouse[index].down;
}

bool Input::released(MouseButton btn)
{
    const auto index = static_cast<i32>(btn);
    return index >= 0 && index < GLFW_MOUSE_BUTTON_LAST && state.mouse[index].released;
}
