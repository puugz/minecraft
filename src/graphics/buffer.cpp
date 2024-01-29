//
// Created by Matej on 30/12/2023.
//

#include "graphics/buffer.h"

using namespace minecraft;

VertexLayout::VertexLayout(const std::initializer_list<VertexAttribute>& elements)
{
    m_elements = elements;
    calculate_offsets_and_stride();
}

void VertexLayout::calculate_offsets_and_stride()
{
    u32 offset = 0;
    m_stride = 0;
    for (auto& attrib : m_elements)
    {
        attrib.offset = offset;
        offset += attrib.size;
        m_stride += attrib.size;
    }
}

// VertexBuffer

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_id);
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Ref<VertexBuffer> VertexBuffer::create()
{
    const auto vertex_buffer = std::make_shared<VertexBuffer>();
    glGenBuffers(1, &vertex_buffer->m_id);

    return vertex_buffer;
}

Ref<VertexBuffer> VertexBuffer::create(f32* vertices, u32 size)
{
    const auto vertex_buffer = std::make_shared<VertexBuffer>();
    glGenBuffers(1, &vertex_buffer->m_id);
    vertex_buffer->set_data(vertices, size);

    return vertex_buffer;
}

void VertexBuffer::set_data(f32* vertices, u32 size) const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

// IndexBuffer

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_id);
}

Ref<IndexBuffer> IndexBuffer::create()
{
    const auto index_buffer = std::make_shared<IndexBuffer>();
    glGenBuffers(1, &index_buffer->m_id);

    return index_buffer;
}

Ref<IndexBuffer> IndexBuffer::create(u32* indices, u32 count)
{
    const auto index_buffer = std::make_shared<IndexBuffer>();
    glGenBuffers(1, &index_buffer->m_id);
    index_buffer->set_data(indices, count);

    return index_buffer;
}

void IndexBuffer::set_data(u32* indices, u32 count)
{
    m_count = count;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(u32), indices, GL_STATIC_DRAW);
}

void IndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void IndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
