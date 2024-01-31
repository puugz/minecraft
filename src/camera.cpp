//
// Created by Matej on 29/12/2023.
//

#include "camera.h"

#include "input.h"

using namespace minecraft;

Camera::Camera(f32 fov, f32 near_plane, f32 far_plane)
{
    this->fov = fov;
    this->m_near_plane = near_plane;
    this->m_far_plane = far_plane;
}

void Camera::update(f32 delta_time, f32 camera_speed)
{
    f32 speed = camera_speed;
    if (Input::ctrl())
        speed *= 2.0f;

    f32 velocity = speed * delta_time;

    if (Input::down(Key::W))
        this->move(this->direction() * velocity);
    if (Input::down(Key::S))
        this->move(-this->direction() * velocity);

    if (Input::down(Key::A))
        this->move(-this->right() * velocity);
    if (Input::down(Key::D))
        this->move(this->right() * velocity);

    if (Input::down(Key::Space))
        this->move(vec3(0.0, 1.0, 0.0) * velocity);
    if (Input::down(Key::LeftShift))
        this->move(vec3(0.0, -1.0, 0.0) * velocity);
}

void Camera::move(vec3 position)
{
    m_position += position;
}

void Camera::move_to(vec3 position)
{
    m_position = position;
}

void Camera::rotate_to(f32 yaw, f32 pitch)
{
    // deg to rad
    yaw = glm::radians(yaw);
    pitch = glm::radians(pitch);

    vec3 new_direction;
    new_direction.x = cos(yaw) * cos(pitch);
    new_direction.y = sin(pitch);
    new_direction.z = sin(yaw) * cos(pitch);

    static constexpr auto world_up = vec3(0.0f, 1.0f, 0.0f);

    m_direction = normalize(new_direction);
    m_right = normalize(cross(m_direction, world_up));
    m_up = normalize(cross(m_right, m_direction));
}

void Camera::handle_mouse(f32 x_offset, f32 y_offset)
{
    m_yaw += x_offset;

    if (m_yaw > 180.0f)
        m_yaw = -180.0f;
    else if (m_yaw < -180.0f)
        m_yaw = 180.0f;

    m_pitch += y_offset;
    m_pitch = glm::clamp(m_pitch, -89.9f, 89.9f);

    rotate_to(m_yaw, m_pitch);
}

mat4 Camera::projection_matrix() const
{
    // TODO: Use framebuffer aspect ratio
    // TODO: Can cache this
    return glm::perspective(glm::radians(fov), 16.f / 9.f, m_near_plane, m_far_plane);
}

mat4 Camera::view_matrix() const
{
    return lookAt(m_position, m_position + m_direction, m_up);
}
