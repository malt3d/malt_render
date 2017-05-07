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
        texture2d::texture2d(const graphics::texture2d& from)
        {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            glGenTextures(1, &m_texture_id);
            glBindTexture(GL_TEXTURE_2D, m_texture_id);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, from.get_resolution().width, from.get_resolution().height, 0,
                    GL_RGB, GL_FLOAT, from.get_buffer().data());

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        }

        texture2d::~texture2d()
        {
            glDeleteTextures(1, &m_texture_id);
        }

        void texture2d::activate(int tex_id) const
        {
            glActiveTexture(GL_TEXTURE0 + tex_id);
            glBindTexture(GL_TEXTURE_2D, m_texture_id);
        }

        texture2d create_texture(rtk::resolution r)
        {
            texture2d res;
            res.m_width = r.width;
            res.m_height = r.height;

            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glGenTextures(1, &res.m_texture_id);

            glBindTexture(GL_TEXTURE_2D, res.m_texture_id);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, r.width, r.height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            return res;
        }

        texture2d create_float_texture(rtk::resolution r)
        {
            texture2d res;
            res.m_width = r.width;
            res.m_height = r.height;

            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glGenTextures(1, &res.m_texture_id);

            glBindTexture(GL_TEXTURE_2D, res.m_texture_id);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, r.width, r.height, 0, GL_RGBA, GL_FLOAT, nullptr);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            return res;
        }

        rtk::resolution texture2d::get_resolution() const
        {
            return { rtk::pixels(m_width), rtk::pixels(m_height) };
        }
    }
}

