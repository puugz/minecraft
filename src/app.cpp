//
// Created by Matej on 29/12/2023.
//

#include "app.h"

#include "camera.h"
#include "input.h"
#include "graphics/graphics.h"
#include "graphics/renderer.h"
#include "graphics/shader.h"

using namespace minecraft;

namespace
{
    bool first_mouse_input = true;
    bool debug_focused = false;

    Options options;

    f32 delta_time = 0.0f;
    f32 last_frame = 0.0f;
    f32 last_mouse_x = 1280 / 2.0f;
    f32 last_mouse_y = 720 / 2.0f;

    f32 sensitivity = 0.1f;
    Camera camera;

    f32 screen_vertices[] = {
        // position     texcoord
        -1.0,  1.0,     0.0, 1.0,
        -1.0, -1.0,     0.0, 0.0,
         1.0, -1.0,     1.0, 0.0,
         1.0,  1.0,     1.0, 1.0,
    };

    u32 screen_indices[] = {
        0, 1, 2,
        2, 3, 0,
    };

    f32 chunk_border_vertices[] = {
        -0.5, -0.5, -0.5,
         0.5, -0.5, -0.5,
         0.5,  0.5, -0.5,
        -0.5,  0.5, -0.5,
        -0.5, -0.5,  0.5,
         0.5, -0.5,  0.5,
         0.5,  0.5,  0.5,
        -0.5,  0.5,  0.5,
    };

    u32 chunk_border_indices[] = {
        0, 1, 1, 2, 2, 3, 3, 0,  // bottom face
        4, 5, 5, 6, 6, 7, 7, 4,  // top face
        0, 4, 1, 5, 2, 6, 3, 7,  // connecting lines
    };
}

// TODO: eh
void handle_mouse(GLFWwindow* window, double x, double y)
{
    if (first_mouse_input)
    {
        last_mouse_x = x;
        last_mouse_y = y;
        first_mouse_input = false;
    }

    f32 x_offset = x - last_mouse_x;
    f32 y_offset = last_mouse_y - y; // reversed since y-coordinates go from bottom to top

    last_mouse_x = x;
    last_mouse_y = y;

    // camera
    if (!debug_focused)
    {
        x_offset *= sensitivity;
        y_offset *= sensitivity;

        camera.handle_mouse(x_offset, y_offset);
    }
}

App::App(Window& window)
    : m_window(window)
{
    m_chunk_shader = Shader::create("assets/shaders/chunk.glsl");

    options.cull_faces = true;
    options.camera = &camera;
    options.camera_speed = 25.f;

    glfwSetCursorPosCallback(m_window.handle(), handle_mouse);
    window.cursor_mode(CursorMode::Disabled);

    m_atlas_texture = Texture2D::create("assets/textures/atlas.png");

    // =================================
    // |        SCREEN SETUP           |
    // =================================
    m_buffer = Target::create(window.width(), window.height());
    m_screen_shader = Shader::create("assets/shaders/screen.glsl");
    m_screen_va = VertexArray::create();

    const auto screen_vb = VertexBuffer::create(screen_vertices, sizeof(screen_vertices));
    screen_vb->set_layout({
        {VertexType::Float2}, // position
        {VertexType::Float2}, // texcoord
    });

    m_screen_va->add_vertex_buffer(screen_vb);
    m_screen_va->set_index_buffer(IndexBuffer::create(screen_indices, std::size(screen_indices)));

    // =================================
    // |        CHUNK BORDER           |
    // =================================
    m_chunk_border_shader = Shader::create("assets/shaders/chunk_border.glsl");
    m_chunk_border_va = VertexArray::create();

    const auto chunk_border_vb = VertexBuffer::create(chunk_border_vertices, sizeof(chunk_border_vertices));
    chunk_border_vb->set_layout({
        {VertexType::Float3}, // position
    });

    m_chunk_border_va->add_vertex_buffer(chunk_border_vb);
    m_chunk_border_va->set_index_buffer(IndexBuffer::create(chunk_border_indices, std::size(chunk_border_indices)));
}

void App::run()
{
    // TODO: ECS??

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!m_window.should_close())
    {
        // update
        update_input();
        update_imgui(&options);

        // this is silly :p
        f32 current_time = glfwGetTime();
        delta_time = current_time - last_frame;
        last_frame = current_time;

        if (Input::pressed(Key::Escape))
        {
            debug_focused = !debug_focused;
            m_window.cursor_mode(debug_focused ? CursorMode::Normal : CursorMode::Disabled);
        }
        if (Input::pressed(Key::F1))
            options.wireframe = !options.wireframe;
        if (Input::pressed(Key::F2))
            options.cull_faces = !options.cull_faces;
        if (Input::pressed(Key::F3))
            options.draw_chunk_border = !options.draw_chunk_border;

        if (!debug_focused)
            camera.update(delta_time, options.camera_speed);

        // render scene
        m_buffer->bind([&]
        {
            m_buffer->clear();
            glEnable(GL_DEPTH_TEST);
            glViewport(0, 0, m_buffer->width(), m_buffer->height());

            glPolygonMode(GL_FRONT_AND_BACK, options.wireframe ? GL_LINE : GL_FILL);
            if (options.cull_faces)
                glEnable(GL_CULL_FACE);
            else
                glDisable(GL_CULL_FACE);

            Renderer::begin_scene(camera);
            {
                m_atlas_texture->bind();
                m_world.render(m_chunk_shader);

                // Draw the chunk the player is in's border
                if (options.draw_chunk_border)
                {
                    auto pos = camera.position();
                    auto cam_chunk = World::world_to_chunk(pos.x, pos.y, pos.z);

                    auto model = mat4(1.0);
                    model = translate(model, vec3( // what the hel
                        cam_chunk.x * CHUNK_WIDTH + CHUNK_WIDTH * 0.5 - 0.5,
                        cam_chunk.y * CHUNK_HEIGHT + CHUNK_HEIGHT * 0.5 - 0.5,
                        cam_chunk.z * CHUNK_DEPTH + CHUNK_DEPTH * 0.5 - 0.5
                    ));
                    model = scale(model, vec3(CHUNK_WIDTH, CHUNK_HEIGHT, CHUNK_DEPTH));

                    glLineWidth(8.0f);
                    glDisable(GL_DEPTH_TEST);
                    Renderer::submit(m_chunk_border_shader, m_chunk_border_va, model, GL_LINES);
                    glLineWidth(1.0f);
                }

                Renderer::end_scene();
            }
        });

        // render the screen quad
        Target::bind_default();
        {
            gfx::clear_color({0.0, 0.0, 0.0, 1.0});
            gfx::clear();
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glViewport(0, 0, m_window.width(), m_window.height());

            glDisable(GL_DEPTH_TEST);
            glBindTexture(GL_TEXTURE_2D, m_buffer->color_attachment());
            m_screen_shader->bind();
            m_screen_va->bind();
            gfx::draw_indexed(m_screen_va);

            render_imgui();
        }

        m_window.poll_events();
        m_window.swap_buffers();
    }
}
