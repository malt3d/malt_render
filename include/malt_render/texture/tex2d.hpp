//
// Created by Mehmet Fatih BAKIR on 01/05/2017.
//

#ifndef MALT_TEX2D_HPP
#define MALT_TEX2D_HPP

#include <glm/vec3.hpp>
#include <glad/glad.h>
#include <gsl/span>
#include <rtk/graphics/size.hpp>

namespace malt {
    namespace graphics {
        class texture2d
        {
            bool m_owns_data;
            std::unique_ptr<glm::vec3[]> m_data;

            int m_width, m_height;

            int index(int x, int y) const;
        public:
            texture2d(rtk::resolution r);
            texture2d(gsl::span<const glm::vec3> data, rtk::resolution r);
            texture2d(std::unique_ptr<glm::vec3[]>&& data, rtk::resolution r);

            const glm::vec3& get_pixel(int x, int y) const;

            /*
             * modifies the given pixel in the texture
             * requires the texture to own the data, ie not being shared
             */
            void set_pixel(int x, int y, const glm::vec3&);

            rtk::resolution get_resolution() const;

            gsl::span<const glm::vec3> get_buffer() const;
        };

        texture2d load_texture(const std::string& path);
    }

    namespace gl {

        template <class elem_type, int channel_count>
        struct texture_traits;

        class texture2d
        {
            int m_width, m_height;
            GLuint m_texture_id;
            int wrap_mode;
            int filter_mode;

            texture2d() = default;

            friend texture2d create_texture(rtk::resolution);
            friend texture2d create_float_texture(rtk::resolution);

        public:
            texture2d(const graphics::texture2d& from);
            ~texture2d();

            void activate(int tex_id) const;

            rtk::resolution get_resolution() const;

            GLuint get_id()
            {
                return m_texture_id;
            }
        };

        texture2d create_texture(rtk::resolution);
        texture2d create_float_texture(rtk::resolution);
    }
}

#endif //MALT_TEX2D_HPP
