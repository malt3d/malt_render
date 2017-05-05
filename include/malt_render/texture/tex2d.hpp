//
// Created by Mehmet Fatih BAKIR on 01/05/2017.
//

#ifndef MALT_TEX2D_HPP
#define MALT_TEX2D_HPP

#include <glm/vec3.hpp>
#include <glad/glad.h>
#include <gsl/span>

namespace malt {
    namespace graphics {
        class texture2d
        {
            bool m_owns_data;
            std::unique_ptr<glm::vec3[]> m_data;

            int m_width, m_height;

            int index(int x, int y) const;
        public:
            texture2d(int width, int height);
            texture2d(gsl::span<const glm::vec3> data, int width, int height);
            texture2d(std::unique_ptr<glm::vec3[]>&& data, int width, int height);

            const glm::vec3& get_pixel(int x, int y) const;

            /*
             * modifies the given pixel in the texture
             * requires the texture to own the data, ie not being shared
             */
            void set_pixel(int x, int y, const glm::vec3&);

            int get_width() const { return m_width; }
            int get_height() const { return m_height; }

            gsl::span<const glm::vec3> get_buffer() const;
        };

        texture2d load_texture(const std::string& path);
    }

    namespace gl {
        class texture2d
        {
            GLuint m_texture_id;
            int wrap_mode;
            int filter_mode;

        public:
            texture2d(const graphics::texture2d& from);
            ~texture2d();

            void activate(int tex_id) const;

            GLuint get_id()
            {
                return m_texture_id;
            }
        };
    }
}

#endif //MALT_TEX2D_HPP
