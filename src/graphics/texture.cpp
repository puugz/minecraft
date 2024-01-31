//
// Created by Matej on 30/12/2023.
//

#include "graphics/texture.h"

#include <stb_image.h>

using namespace minecraft;

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &m_id);
}

Ref<Texture2D> Texture2D::create(const std::string& path)
{
    const auto texture_2d = std::make_shared<Texture2D>();
    stbi_set_flip_vertically_on_load(true);

    i32 width, height, channels;
    u8* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    APP_ASSERT(data, "Failed to load image!");

    texture_2d->m_width = width;
    texture_2d->m_height = height;

    glGenTextures(1, &texture_2d->m_id);
    glBindTexture(GL_TEXTURE_2D, texture_2d->m_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    GLenum format;
    if (channels == 1)
        format = GL_RED;
    else if (channels == 3)
        format = GL_RGB;
    else if (channels == 4)
        format = GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    spdlog::debug("Loaded texture {}", path);

    stbi_image_free(data);

    return texture_2d;
}

void Texture2D::bind(u32 slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

// TextureCube

TextureCube::~TextureCube()
{
    glDeleteTextures(1, &m_id);
}

Ref<TextureCube> TextureCube::create(std::vector<std::string> faces)
{
    const auto texture_cube = std::make_shared<TextureCube>();
    stbi_set_flip_vertically_on_load(false);

    glGenTextures(1, &texture_cube->m_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture_cube->m_id);

    i32 width, height, channels;
    for (i32 i = 0; i < faces.size(); i++)
    {
        u8* data = stbi_load(faces[i].c_str(), &width, &height, &channels, 0);
        APP_ASSERT(data, "Failed to load image!");

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                        0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return texture_cube;
}

void TextureCube::bind(u32 slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
}
