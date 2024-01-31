//
// Created by Matej on 29/12/2023.
//

#pragma once

#include "camera.h"
#include "common.h"
#include "window.h"
#include "graphics/shader.h"
#include "graphics/target.h"
#include "graphics/texture.h"
#include "graphics/vertex_array.h"
#include "world/world.h"

namespace minecraft
{
    struct AppOptions
    {
        bool wireframe;
        bool cull_faces;
        bool draw_chunk_border;
        Camera* camera;
        float camera_speed;
    };

    class App
    {
    public:
        App(Window& window);

        void init_imgui() const;

        void run();

    private:
        Window& m_window;
        World m_world;

        Ref<Target> m_buffer;
        Ref<Shader> m_screen_shader;
        Ref<VertexArray> m_screen_va;

        Ref<Shader> m_chunk_border_shader;
        Ref<VertexArray> m_chunk_border_va;

        Ref<Shader> m_chunk_shader;
        Ref<Texture2D> m_atlas_texture;

        void update_imgui(AppOptions* options);

        void render_imgui() const;

        void update_input() const;
    };
}
