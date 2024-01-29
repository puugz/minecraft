//
// Created by Matej on 31/12/2023.
//

#pragma once

#include "camera.h"
#include "common.h"
#include "shader.h"
#include "vertex_array.h"

namespace minecraft
{
    class Renderer
    {
    public:
        static void begin_scene(const Camera& camera);
        static void end_scene();

        static void submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertex_array, const mat4& model = mat4(1.0f), GLenum mode = GL_TRIANGLES);

    private:
        struct SceneData
        {
            mat4 view_matrix;
            mat4 projection_matrix;
        };

        static SceneData* m_scene_data;
    };
} // minecraft
