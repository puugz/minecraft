//
// Created by Matej on 29/12/2023.
//

#pragma once

#include "common.h"
#include "world/world.h"

namespace minecraft
{
    class Camera
    {
    public:
        explicit Camera(f32 fov = 70.f, f32 near_plane = 0.1f, f32 far_plane = 1000.f);

        f32 fov;

        void update(f32 delta_time, f32 camera_speed);

        void move(vec3 position);
        void move_to(vec3 position);
        void rotate_to(f32 yaw, f32 pitch);

        void handle_mouse(f32 x_offset, f32 y_offset);

        vec3 position() const { return m_position; }
        vec3 direction() const { return m_direction; }
        vec3 right() const { return m_right; }
        vec3 up() const { return m_up; }

        f32 yaw() const { return m_yaw; }
        f32 pitch() const { return m_pitch; }

        mat4 projection_matrix() const;
        mat4 view_matrix() const;

    private:
        vec3 m_position = vec3(WORLD_WIDTH / 2.0f * CHUNK_WIDTH, WORLD_HEIGHT * CHUNK_HEIGHT, WORLD_DEPTH / 2.0f * CHUNK_DEPTH);
        vec3 m_direction = vec3(0.0f, 0.0f, -1.0f);
        vec3 m_right = vec3(1.0f, 0.0f, 0.0f);
        vec3 m_up = vec3(0.0f, 1.0f, 0.0f);

        f32 m_yaw = -90.0f;
        f32 m_pitch = 0.0f;

        f32 m_near_plane;
        f32 m_far_plane;
    };
}
