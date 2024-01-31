//
// Created by Matej on 31/12/2023.
//

#include "graphics/renderer.h"

#include "graphics/graphics.h"
#include "graphics/shader.h"

using namespace minecraft;

Renderer::SceneData* Renderer::m_scene_data = new SceneData;

void Renderer::begin_scene(const Camera& camera)
{
    m_scene_data->view_matrix = camera.view_matrix();
    m_scene_data->projection_matrix = camera.projection_matrix();
}

void Renderer::end_scene()
{
}

void Renderer::submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertex_array, const mat4& model, GLenum mode)
{
    shader->bind();
    shader->set("u_model", model);
    shader->set("u_view", m_scene_data->view_matrix);
    shader->set("u_projection", m_scene_data->projection_matrix);

    vertex_array->bind();
    gfx::draw_indexed(vertex_array, mode);
}
