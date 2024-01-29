//
// Created by Matej on 30/12/2023.
//

#pragma once

#include "common.h"

namespace minecraft
{
    class Texture
    {
    public:
        virtual ~Texture() = default;

        virtual u32 id() const = 0;

        virtual void bind(u32 slot = 0) const = 0;
    };

    class Texture2D : public Texture
    {
    public:
        ~Texture2D() override;

        static Ref<Texture2D> create(const std::string& path);

        u32 id() const override { return m_id; }
        u32 width() const { return m_width; }
        u32 height() const { return m_height; }

        void bind(u32 slot = 0) const override;

    private:
        u32 m_id;

        u32 m_width;
        u32 m_height;
    };

    class TextureCube : public Texture
    {
    public:
        ~TextureCube() override;

        static Ref<TextureCube> create(std::vector<std::string> faces);

        u32 id() const override { return m_id; }

        void bind(u32 slot = 0) const override;

    private:
        u32 m_id;
    };
}
