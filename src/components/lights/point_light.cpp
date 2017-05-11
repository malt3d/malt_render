//
// Created by Mehmet Fatih BAKIR on 30/04/2017.
//

#include <malt_render/components/lights/point_light.hpp>
#include <malt/component_mgr_impl.hpp>

glm::vec3 point_light::get_intensity()
{
    return m_intensity;
}

MALT_IMPLEMENT_COMP(point_light)