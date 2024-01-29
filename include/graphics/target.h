//
// Created by Matej on 29/12/2023.
//

#pragma once

#include "common.h"

namespace minecraft
{
    class Target
    {
    public:
        ~Target();

        static Ref<Target> create(i32 width, i32 height);
        static void bind_default();

        void bind(Fn<void>& callback) const;

        u32 id() const { return m_id; }
        u32 color_attachment() const { return m_color_attachment; }

        i32 width() const { return m_width; }
        i32 height() const { return m_height; }

        void clear() const;
    private:
        u32 m_id;
        u32 m_color_attachment;

        i32 m_width;
        i32 m_height;
    };

    // Dummy backbuffer target
    class Backbuffer : public Target
    {
        // TODO: impl
    };
}
