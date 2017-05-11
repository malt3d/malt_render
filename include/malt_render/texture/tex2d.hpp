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
        enum class channel_type : uint8_t
        {
            real,
            integer
        };

        enum class pixel_format : uint8_t
        {
            gray_byte,
            rgb_byte,
            rgba_byte,

            gray_half,
            rgb_half,
            rgba_half,

            gray_float,
            rgb_float,
            rgba_float
        };

        template <channel_type c_type, int bits_per_channel, int channel_count> struct get_format;

        template <> struct get_format<channel_type::real, 16, 1> { static constexpr auto value = pixel_format::gray_half; };
        template <> struct get_format<channel_type::real, 16, 3> { static constexpr auto value = pixel_format::rgb_half; };
        template <> struct get_format<channel_type::real, 16, 4> { static constexpr auto value = pixel_format::rgba_half; };

        template <> struct get_format<channel_type::real, 32, 1> { static constexpr auto value = pixel_format::gray_float; };
        template <> struct get_format<channel_type::real, 32, 3> { static constexpr auto value = pixel_format::rgb_float; };
        template <> struct get_format<channel_type::real, 32, 4> { static constexpr auto value = pixel_format::rgba_float; };

        template <> struct get_format<channel_type::integer, 8, 1> { static constexpr auto value = pixel_format::gray_byte; };
        template <> struct get_format<channel_type::integer, 8, 3> { static constexpr auto value = pixel_format::rgb_byte; };
        template <> struct get_format<channel_type::integer, 8, 4> { static constexpr auto value = pixel_format::rgba_byte; };

        struct unsafe_texture
        {
            /*
             * stores the raw texture data for this texture
             */
            void* m_data;

            uint16_t m_width, m_height;
            pixel_format m_fmt;
        };

        class texture2d
                : public unsafe_texture
        {
            bool m_owns_data;
            std::unique_ptr<glm::vec3[]> m_data;

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
            uint16_t m_width, m_height;
            GLuint m_texture_id;

            graphics::pixel_format m_fmt;
            int wrap_mode;
            int filter_mode;

            texture2d() = default;

            friend texture2d create_texture(rtk::resolution, graphics::pixel_format);
            friend class framebuffer;

        public:
            texture2d(const graphics::unsafe_texture& tex);
            ~texture2d();

            void activate(int tex_id) const;

            rtk::resolution get_resolution() const;
        };

        texture2d create_texture(rtk::resolution, graphics::pixel_format);
    }
}

#endif //MALT_TEX2D_HPP
