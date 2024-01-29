//
// Created by Matej on 31/12/2023.
//

#pragma once

#include "common.h"
#include "vertex_array.h"

namespace minecraft::gfx
{
    inline void clear_color(const vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    inline void clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    inline void draw_indexed(const Ref<VertexArray>& vertex_array, GLenum mode = GL_TRIANGLES)
    {
        glDrawElements(mode, vertex_array->index_buffer()->count(), GL_UNSIGNED_INT, nullptr);
    }
}
