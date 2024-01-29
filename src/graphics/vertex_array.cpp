//
// Created by Matej on 31/12/2023.
//

#include "graphics/vertex_array.h"

using namespace minecraft;

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_id);
}

Ref<VertexArray> VertexArray::create()
{
    const auto resource = std::make_shared<VertexArray>();

    glGenVertexArrays(1, &resource->m_id);
    glBindVertexArray(resource->m_id);

    return resource;
}

void VertexArray::bind() const
{
    glBindVertexArray(m_id);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::add_vertex_buffer(const Ref<VertexBuffer>& vertex_buffer)
{
    APP_ASSERT(vertex_buffer->get_layout().elements().size(), "Vertex buffer has no layout.");

    glBindVertexArray(m_id);
    vertex_buffer->bind();

    u32 index = 0;
    const auto& layout = vertex_buffer->get_layout();
    for (const auto& attrib : layout)
    {
        glVertexAttribPointer(
            index,
            attrib.component_count(),
            vertex_type_to_gl_type(attrib.type),
            attrib.normalized ? GL_TRUE : GL_FALSE,
            layout.stride(),
            (const void*)attrib.offset
        );
        glEnableVertexAttribArray(index);
        index++;
    }

    m_vertex_buffers.push_back(vertex_buffer);
}

void VertexArray::set_index_buffer(const Ref<IndexBuffer>& index_buffer)
{
    glBindVertexArray(m_id);
    index_buffer->bind();

    m_index_buffer = index_buffer;
}

const std::vector<Ref<VertexBuffer>>& VertexArray::vertex_buffers() const
{
    return m_vertex_buffers;
}

const Ref<IndexBuffer>& VertexArray::index_buffer() const
{
    return m_index_buffer;
}
