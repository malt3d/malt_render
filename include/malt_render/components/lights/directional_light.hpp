//
// Created by Mehmet Fatih BAKIR on 30/04/2017.
//

#ifndef MALT_DIRECTIONAL_LIGHT_HPP
#define MALT_DIRECTIONAL_LIGHT_HPP

#include <malt/component.hpp>
#include <glm/vec3.hpp>

class directional_light : public malt::component
{
    glm::vec3 m_intensity = {0.5, 0.5, 0.5};
public:

    void set_intensity(const glm::vec3&);
    glm::vec3 get_intensity();
    glm::vec3 get_light_direction();
};

#endif //MALT_DIRECTIONAL_LIGHT_HPP
