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
        texture2d::texture2d(gsl::span<const glm::vec3> data, int width, int height)
                :texture2d(width, height)
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

        texture2d::texture2d(int width, int height)
        {
            m_data = std::make_unique<glm::vec3[]>(width*height);
            m_width = width;
            m_height = height;
            m_owns_data = true;
        }

        gsl::span<const glm::vec3> texture2d::get_buffer() const
        {
            return { m_data.get(), m_width * m_height };
        }

        texture2d::texture2d(std::unique_ptr<glm::vec3[]>&& data, int width, int height)
        {
            m_data = std::move(data);
            m_width = width;
            m_height = height;
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
            auto res = texture2d(std::move(vec3_data), w, h);
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

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, from.get_width(), from.get_height(), 0,
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
    }
}

