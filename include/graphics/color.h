//
// Created by Matej on 31/01/2024.
//

#pragma once

#include "../common.h"

namespace minecraft
{
    struct Color
    {
        u8 r;
        u8 g;
        u8 b;
        u8 a;

        constexpr Color()
            : r(0), g(0), b(0), a(0) {}

        constexpr Color(const i32 rgb)
            : r((rgb >> 16) & 0xFF),
              g((rgb >> 8) & 0xFF),
              b(rgb & 0xFF),
              a(255) {}

        constexpr Color(const i32 rgb, const f32 alpha)
            : r(((rgb >> 16) & 0xFF) * alpha),
              g(((rgb >> 8) & 0xFF) * alpha),
              b((rgb & 0xFF) * alpha),
              a(255 * alpha) {}

        constexpr Color(const u8 r, const u8 g, const u8 b)
            : r(r), g(g), b(b), a(255) {}

        constexpr Color(const u8 r, const u8 g, const u8 b, const u8 a)
            : r(r), g(g), b(b), a(a) {}

        constexpr u32 to_rgba() const
        {
            return (r << 24) | (g << 16) | (b << 8) | a;
        }

        constexpr u32 to_rgb() const
        {
            return (r << 16) | (g << 8) | b;
        }

        constexpr Color& operator=(i32 rgb)
        {
            r = (rgb >> 16) & 0xFF;
            g = (rgb >> 8) & 0xFF;
            b = rgb & 0xFF;
            a = 255;
            return *this;
        }

        constexpr bool operator ==(const Color& other) const
        {
            return r == other.r && g == other.g && b == other.b && a == other.a;
        }

        constexpr bool operator !=(const Color& other) const
        {
            return !(*this == other);
        }

        static const Color black;
        static const Color white;
        static const Color red;
        static const Color green;
        static const Color blue;
        static const Color yellow;
        static const Color magenta;
        static const Color cyan;
    };

    inline const Color Color::black = Color(0, 0, 0);
    inline const Color Color::white = Color(255, 255, 255);
    inline const Color Color::red = Color(255, 0, 0);
    inline const Color Color::green = Color(0, 255, 0);
    inline const Color Color::blue = Color(0, 0, 255);
    inline const Color Color::yellow = Color(255, 255, 0);
    inline const Color Color::magenta = Color(255, 0, 255);
    inline const Color Color::cyan = Color(0, 255, 255);
} // minecraft
