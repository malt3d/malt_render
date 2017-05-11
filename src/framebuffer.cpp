//
// Created by fatih on 5/12/17.
//

#include <stdexcept>
#include <utility>
#include "malt_render/framebuffer.hpp"
#include <malt_render/texture/tex2d.hpp>

malt::gl::framebuffer::framebuffer(const malt::gl::texture2d& render_to)
{
    glGenFramebuffers(1, &m_fb_id);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        throw std::runtime_error("error creating framebuffer");
    }
    m_render_to = &render_to;
}

malt::gl::framebuffer::framebuffer(malt::gl::framebuffer&& rhs)
{
    m_fb_id = std::exchange(rhs.m_fb_id, 0);
}

malt::gl::framebuffer::~framebuffer()
{
    glDeleteFramebuffers(1, &m_fb_id);
}

void malt::gl::framebuffer::activate() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_fb_id);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_render_to->m_texture_id, 0);
}

void ::malt::gl::reset_framebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
