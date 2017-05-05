//
// Created by Mehmet Fatih BAKIR on 30/04/2017.
//

#ifndef MALT_RENDER_CTX_HPP
#define MALT_RENDER_CTX_HPP

#include <glm/mat4x4.hpp>

struct directional_light_data
{
    glm::vec3 intensity;
    glm::vec3 direction;
};

struct point_light_data
{
    glm::vec3 intensity;
    glm::vec3 position;
};

struct render_ctx
{
    glm::mat4 vp;
    glm::vec3 cam_position;
    glm::vec3 ambient_light;
    directional_light_data dir_light;
    point_light_data point_lights[8];
    int point_light_size;
};

#endif //MALT_RENDER_CTX_HPP
