//
// Created by Matej on 02/01/2024.
//

#include "graphics/target.h"

using namespace minecraft;

Target::~Target()
{
    glDeleteFramebuffers(1, &m_id);
}

Ref<Target> Target::create(i32 width, i32 height)
{
    const auto target = std::make_shared<Target>();
    target->m_width = width;
    target->m_height = height;

    glGenFramebuffers(1, &target->m_id);

    target->bind([&]
    {
        glGenTextures(1, &target->m_color_attachment);
        glBindTexture(GL_TEXTURE_2D, target->m_color_attachment);

        // give an empty image to OpenGL ( the last "0" )
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // attach the texture to the framebuffer
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, target->m_color_attachment, 0);

        // create a renderbuffer object for depth and stencil attachment
        // (write-only depth and stencil buffer)
        u32 rbo;
        glGenRenderbuffers(1, &rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        // attach the renderbuffer object to the framebuffer
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

        APP_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is not complete!");
    });

    spdlog::debug("Created target {}x{} with id {}.", width, height, target->m_id);

    return target;
}

void Target::bind_default()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Target::bind(Fn<void>& callback) const
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);
    callback();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Target::clear() const
{
    glClearColor(114 / 255.f, 188 / 255.f, 219 / 255.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
