//
// Created by fatih on 4/30/17.
//

#ifndef MALT_MATERIAL_HPP
#define MALT_MATERIAL_HPP

#include <malt/component.hpp>
#include <rtk/gl/program.hpp>
#include <glm/glm.hpp>

class material : public malt::component
{
private:
    rtk::gl::program m_program;
    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;
    float m_phong_exponent;

public:
    void Handle(malt::init);
    void Handle(malt::start);

    rtk::gl::program& get_program();
    const rtk::gl::program& get_program() const;
    void set_ambient(const glm::vec3& ambient);
    void set_diffuse(const glm::vec3& diffuse);
    void set_specular(const glm::vec3& specular);
    void set_phong_exponent(float phong_exponent);
};

#endif //MALT_MATERIAL_HPP
