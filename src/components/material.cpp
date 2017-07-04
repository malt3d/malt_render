//
// Created by fatih on 4/30/17.
//

#include <malt_render/components/material.hpp>
#include <malt/detail/component_mgr_impl.hpp>
#include <fstream>
#include <malt_render/messages.hpp>
#include <rtk/gl/shader.hpp>
#include <malt_asset/text_asset.hpp>
#include <malt_asset/assets.hpp>

MALT_IMPLEMENT_COMP(malt::material)
namespace malt {

    void material::Handle(malt::start) {
        m_shader.set_variable("material.ambient", m_ambient);
        m_shader.set_variable("material.diffuse", m_diffuse);
        m_shader.set_variable("material.specular", m_specular);
        m_shader.set_variable("material.phong_exponent", m_phong_exponent);
    }

    rtk::gl::program &material::get_shader() {
        return m_shader;
    }

    const rtk::gl::program &material::get_shader() const {
        return m_shader;
    }

    void material::set_ambient(const glm::vec3 &ambient) {
        m_ambient = ambient;
    }

    void material::set_diffuse(const glm::vec3 &diffuse) {
        m_diffuse = diffuse;
    }

    void material::set_specular(const glm::vec3 &specular) {
        m_specular = specular;
    }

    void material::set_phong_exponent(float phong_exponent) {
        m_phong_exponent = phong_exponent;
    }

    void material::Handle(malt::init) {
        m_shader = std::move(*malt::asset::load<rtk::gl::program>("malt_shaders/phong.s.yml"));
    }
}