//
// Created by Matej on 31/12/2023.
//

#pragma once

#include "common.h"
#include "buffer.h"

namespace minecraft
{
    class VertexArray
    {
    public:
        ~VertexArray();

        static Ref<VertexArray> create();

        void bind() const;
        void unbind() const;

        void add_vertex_buffer(const Ref<VertexBuffer>& vertex_buffer);
        void set_index_buffer(const Ref<IndexBuffer>& index_buffer);

        const std::vector<Ref<VertexBuffer>>& vertex_buffers() const;
        const Ref<IndexBuffer>& index_buffer() const;
    private:
        u32 m_id;

        std::vector<Ref<VertexBuffer>> m_vertex_buffers;
        Ref<IndexBuffer> m_index_buffer;
    };
}
