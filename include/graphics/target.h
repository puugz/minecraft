//
// Created by Matej on 29/12/2023.
//

#pragma once

#include "common.h"
#include "color.h"

namespace minecraft
{
    class Target
    {
    public:
        ~Target();

        static Ref<Target> create(i32 width, i32 height);
        static void bind_default();

        void bind(Fn<void>& callback) const;

        void resize(i32 width, i32 height);

        u32 id() const { return m_id; }
        u32 color_attachment() const { return m_color_attachment; }

        i32 width() const { return m_width; }
        i32 height() const { return m_height; }

        void set_clear_color(const Color& color) { m_clear_color = color; }

        void clear() const;
    private:
        u32 m_id;
        u32 m_color_attachment;

        i32 m_width;
        i32 m_height;

        Color m_clear_color = Color::black;
    };

    // TODO: Dummy backbuffer target
    class Backbuffer : public Target
    {
    };
}
