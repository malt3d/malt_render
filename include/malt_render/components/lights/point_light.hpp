//
// Created by Mehmet Fatih BAKIR on 30/04/2017.
//

#pragma once

#include <malt/component.hpp>
#include <glm/vec3.hpp>

class point_light : public malt::component
{
    glm::vec3 m_intensity;
public:

    glm::vec3 get_intensity();
};
