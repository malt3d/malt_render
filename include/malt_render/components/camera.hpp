//
// Created by musti on 30.04.2017.
//

#ifndef MALT_CAMERA_HPP
#define MALT_CAMERA_HPP

#include <malt/component.hpp>
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include <glm/glm.hpp>
#include <malt_render/malt_render_fwd.hpp>

class camera : public malt::component
{
private:
    glm::mat4 m_view_matrix;
    glm::mat4 m_projection_matrix;
    glm::mat4 m_vp_matrix;
    float m_fov = 1.0471975512f; // 60 degrees
    float m_aspect_ratio = 1.333333f; //800 over 600
    float m_near_plane = 0.1f;
    float m_far_plane = 100.0f;
    bool m_update_projection_matrix = true;

    glm::vec2 viewport_pos = {0.f, 0.f};
    glm::vec2 viewport_size = {1.f, 1.f};

    malt::display* display;

public:
    void Handle(malt::update);

    glm::mat4& get_vp_matrix();
    const glm::mat4& get_vp_matrix() const;

    void set_display(malt::display* d) { display = d;}

    void set_fov(float fov);
    void reset_aspect();
    void set_aspect_ratio(float aspect_ratio);
    void set_near_plane(float near_plane);
    void set_far_plane(float far_plane);

    void activate() const;
};

#endif //MALT_CAMERA_HPP