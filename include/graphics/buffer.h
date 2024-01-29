//
// Created by Matej on 30/12/2023.
//

#pragma once

#include "common.h"

namespace minecraft
{
    enum class VertexType
    {
        None,
        Float,
        Float2,
        Float3,
        Float4,
        Byte4,
        UByte4,
        Short2,
        UShort2,
        Short4,
        UShort4,
    };

    static GLenum vertex_type_to_gl_type(VertexType type)
    {
        switch (type)
        {
        case VertexType::Float:     return GL_FLOAT;
        case VertexType::Float2:    return GL_FLOAT;
        case VertexType::Float3:    return GL_FLOAT;
        case VertexType::Float4:    return GL_FLOAT;
        case VertexType::Byte4:     return GL_BYTE;
        case VertexType::UByte4:    return GL_UNSIGNED_BYTE;
        case VertexType::Short2:    return GL_SHORT;
        case VertexType::UShort2:   return GL_UNSIGNED_SHORT;
        case VertexType::Short4:    return GL_SHORT;
        case VertexType::UShort4:   return GL_UNSIGNED_SHORT;
        }

        APP_ASSERT(false, "Unknown vertex type!");
        return 0;
    }

    static u32 vertex_type_size(VertexType type)
    {
        switch (type)
        {
        case VertexType::Float:     return 4;
        case VertexType::Float2:    return 4 * 2;
        case VertexType::Float3:    return 4 * 3;
        case VertexType::Float4:    return 4 * 4;
        case VertexType::Byte4:     return 1 * 4;
        case VertexType::UByte4:    return 1 * 4;
        case VertexType::Short2:    return 2 * 2;
        case VertexType::UShort2:   return 2 * 2;
        case VertexType::Short4:    return 2 * 4;
        case VertexType::UShort4:   return 2 * 4;
        }

        APP_ASSERT(false, "Unknown vertex type!");
        return 0;
    }

    struct VertexAttribute
    {
        VertexType type;
        u32 size;
        u32 offset;
        bool normalized;

        VertexAttribute() = default;

        VertexAttribute(VertexType type, bool normalized = false)
            : type(type), size(vertex_type_size(type)), offset(0), normalized(normalized)
        {}

        u32 component_count() const
        {
            switch (type)
            {
            case VertexType::Float:     return 1;
            case VertexType::Float2:    return 2;
            case VertexType::Float3:    return 3;
            case VertexType::Float4:    return 4;
            case VertexType::Byte4:     return 4;
            case VertexType::UByte4:    return 4;
            case VertexType::Short2:    return 2;
            case VertexType::UShort2:   return 2;
            case VertexType::Short4:    return 4;
            case VertexType::UShort4:   return 4;
            }

            APP_ASSERT(false, "Unknown vertex type!");
            return 0;
        }
    };

    class VertexLayout
    {
    public:
        VertexLayout() = default;
        VertexLayout(const std::initializer_list<VertexAttribute>& elements);

        u32 stride() const { return m_stride; }

        const std::vector<VertexAttribute>& elements() const { return m_elements; }

        std::vector<VertexAttribute>::iterator begin() { return m_elements.begin(); }
        std::vector<VertexAttribute>::iterator end() { return m_elements.end(); }
        std::vector<VertexAttribute>::const_iterator begin() const { return m_elements.begin(); }
        std::vector<VertexAttribute>::const_iterator end() const { return m_elements.end(); }
    private:
        std::vector<VertexAttribute> m_elements;
        u32 m_stride;

        void calculate_offsets_and_stride();
    };

    class VertexBuffer
    {
    public:
        ~VertexBuffer();

        static Ref<VertexBuffer> create();
        static Ref<VertexBuffer> create(f32* vertices, u32 size);

        void set_data(f32* vertices, u32 size) const;

        void bind() const;
        void unbind() const;

        void set_layout(const VertexLayout& layout) { m_layout = layout; }
        const VertexLayout& get_layout() const { return m_layout; }

    private:
        u32 m_id;
        VertexLayout m_layout;
    };

    class IndexBuffer
    {
    public:
        ~IndexBuffer();

        static Ref<IndexBuffer> create();
        static Ref<IndexBuffer> create(u32* indices, u32 count);

        void set_data(u32* indices, u32 count);

        void bind() const;
        void unbind() const;

        u32 count() const { return m_count; }

    private:
        u32 m_id;
        u32 m_count;
    };
}
