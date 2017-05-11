//
// Created by fatih on 5/12/17.
//

#pragma once

#include <malt_render/render_fwd.hpp>
#include <glad/glad.h>

namespace malt
{
namespace gl
{
    class framebuffer
    {
    public:
        explicit framebuffer(const texture2d&);
        framebuffer(const framebuffer&) = delete;
        framebuffer(framebuffer&&);
        ~framebuffer();

        const texture2d* get_texture() const { return m_render_to; }

        void activate() const;

    private:
        const texture2d* m_render_to;
        GLuint m_fb_id;
    };

    void reset_framebuffer();
}
}



