//
// Created by Mehmet Fatih BAKIR on 01/05/2017.
//

#include <malt_render/texture/tex2d.hpp>
#include <SOIL/SOIL.h>
#include <string>

namespace malt {
    class texture_not_editable
    {
    };
    namespace graphics {
        texture2d::texture2d(gsl::span<const glm::vec3> data, rtk::resolution r)
                :texture2d(r)
        {
            std::copy(data.begin(), data.end(), m_data.get());
        }

        const glm::vec3& texture2d::get_pixel(int x, int y) const
        {
            return m_data[index(x, y)];
        }

        void texture2d::set_pixel(int x, int y, const glm::vec3& col)
        {
            if (!m_owns_data) throw texture_not_editable{};
            m_data[index(x, y)] = col;
        }

        int texture2d::index(int x, int y) const
        {
            return y*m_width+x;
        }

        gsl::span<const glm::vec3> texture2d::get_buffer() const
        {
            return { m_data.get(), m_width * m_height };
        }

        texture2d::texture2d(std::unique_ptr<glm::vec3[]>&& data, rtk::resolution r)
        {
            m_data = std::move(data);
            m_width = r.width;
            m_height = r.height;

            unsafe_texture::m_data = m_data.get();
            m_fmt = pixel_format::rgb_float;

            m_owns_data = true;
        }

        rtk::resolution texture2d::get_resolution() const
        {
            return { rtk::pixels(m_width), rtk::pixels(m_height) };
        }

        texture2d::texture2d(rtk::resolution r)
        {
            m_width = r.width;
            m_height = r.height;
            m_data = std::make_unique<glm::vec3[]>(m_width*m_height);

            unsafe_texture::m_data = m_data.get();
            m_fmt = pixel_format::rgb_float;

            m_owns_data = true;
        }

        texture2d load_texture(const std::string& path)
        {
            int w, h;
            auto data = SOIL_load_image(path.c_str(), &w, &h, 0, SOIL_LOAD_RGB);
            auto vec3_data = std::make_unique<glm::vec3[]>(w * h);
            for (int i = 0; i < w * h * 3; i += 3)
            {
                vec3_data[i / 3] = glm::vec3(data[i], data[i + 1], data[i + 2]) / 255.f;
            }
            auto res = texture2d(std::move(vec3_data), rtk::resolution(rtk::pixels(w), rtk::pixels(h)));
            SOIL_free_image_data(data);
            return res;
        }
    }

    namespace gl
    {
        texture2d::~texture2d()
        {
            glDeleteTextures(1, &m_texture_id);
        }

        void texture2d::activate(int tex_id) const
        {
            glActiveTexture(GL_TEXTURE0 + tex_id);
            glBindTexture(GL_TEXTURE_2D, m_texture_id);
        }

        struct gl_type
        {
            GLenum internal;
            GLenum format;
            GLenum type;
        };

        constexpr gl_type to_gl_type(graphics::pixel_format fmt)
        {
            using namespace graphics;
            switch (fmt)
            {
            case pixel_format::gray_byte: return {GL_R8, GL_RED, GL_UNSIGNED_BYTE};
            case pixel_format::rgb_byte: return {GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE};
            case pixel_format::rgba_byte: return {GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE};

            case pixel_format::gray_half: return {GL_R8, GL_RED, GL_HALF_FLOAT};
            case pixel_format::rgb_half: return {GL_RGB8, GL_RGB, GL_HALF_FLOAT};
            case pixel_format::rgba_half: return {GL_RGBA8, GL_RGBA, GL_HALF_FLOAT};

            case pixel_format::gray_float: return {GL_R8, GL_RED, GL_FLOAT};
            case pixel_format::rgb_float: return {GL_RGB8, GL_RGB, GL_FLOAT};
            case pixel_format::rgba_float: return {GL_RGBA8, GL_RGBA, GL_FLOAT};
            }
        }

        rtk::resolution texture2d::get_resolution() const
        {
            return { rtk::pixels(m_width), rtk::pixels(m_height) };
        }

        texture2d::texture2d(const graphics::unsafe_texture& tex)
        {
            m_width = tex.m_width;
            m_height = tex.m_height;
            m_fmt = tex.m_fmt;

            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            glGenTextures(1, &m_texture_id);
            glBindTexture(GL_TEXTURE_2D, m_texture_id);

            auto gl_t = to_gl_type(m_fmt);

            glTexImage2D(GL_TEXTURE_2D, 0, gl_t.internal, m_width, m_height, 0, gl_t.format, gl_t.type, tex.m_data);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        }

        texture2d create_texture(rtk::resolution r, graphics::pixel_format fmt)
        {
            texture2d res;
            res.m_width = r.width;
            res.m_height = r.height;
            res.m_fmt = fmt;

            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            glGenTextures(1, &res.m_texture_id);
            glBindTexture(GL_TEXTURE_2D, res.m_texture_id);

            auto gl_t = to_gl_type(fmt);

            glTexImage2D(GL_TEXTURE_2D, 0, gl_t.internal, res.m_width, res.m_height, 0, gl_t.format, gl_t.type, nullptr);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            return res;
        }

    }
}

