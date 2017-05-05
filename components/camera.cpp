//
// Created by musti on 30.04.2017.
//

#include <malt/component_mgr_impl.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <malt_basic/components/transform.hpp>
#include <malt_render/components/camera.hpp>
#include <malt_render/display.hpp>
#include <rtk/utility.hpp>

void camera::Handle(malt::update)
{
    auto camera_transform = get_component<malt::transform>();
    auto right = camera_transform->get_right();
    auto up = camera_transform->get_up();
    auto forward = camera_transform->get_forward();
    auto& position = camera_transform->get_pos();

    m_view_matrix = glm::lookAt(position, position + forward, up);

    if (m_update_projection_matrix)
    {
        m_projection_matrix = glm::perspective(m_fov, m_aspect_ratio, m_near_plane, m_far_plane);
        m_update_projection_matrix = false;
    }

    m_vp_matrix = m_projection_matrix * m_view_matrix;
}

void camera::set_fov(float fov)
{
    m_fov = fov;
    m_update_projection_matrix = true;
}

void camera::set_aspect_ratio(float aspect_ratio)
{
    m_aspect_ratio = aspect_ratio;
    m_update_projection_matrix = true;
}

void camera::set_near_plane(float near_plane)
{
    m_near_plane = near_plane;
    m_update_projection_matrix = true;
}

void camera::set_far_plane(float far_plane)
{
    m_far_plane = far_plane;
    m_update_projection_matrix = true;
}

glm::mat4 &camera::get_vp_matrix()
{
    return m_vp_matrix;
}

const glm::mat4 &camera::get_vp_matrix() const
{
    return m_vp_matrix;
}

void camera::reset_aspect()
{
    auto res = display->get_resolution();
    float aspect = float(res.width) / res.height;
    set_aspect_ratio(aspect);
}

void camera::activate() const
{
    rtk::size<rtk::pixels> res{ rtk::pixels(display->get_resolution().width * viewport_size.x),
                         rtk::pixels(display->get_resolution().height * viewport_size.y) };

    rtk::point2d<rtk::pixels> pos
            { rtk::pixels(display->get_resolution().width * viewport_pos.x),
              rtk::pixels(display->get_resolution().height * viewport_pos.y) };

    rtk::screen_rect r{pos, res};
    rtk::set_viewport(r);
}

MALT_IMPLEMENT_COMP(camera)