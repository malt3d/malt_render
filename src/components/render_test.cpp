//
// Created by musti on 30.04.2017.
//

#include <malt_render/components/render_test.hpp>
#include <malt_render/components/material.hpp>
#include <rtk/gl/mesh.hpp>
#include <malt/detail/component_mgr_impl.hpp>
#include <malt_render/components/mesh_renderer.hpp>
#include <rtk/asset/mesh_import.hpp>
#include <rtk/mesh_ops.hpp>
#include <rtk/texture/tex2d.hpp>
#include <malt_asset/assets.hpp>

void render_test::Handle(malt::start)
{
    auto phong_material = get_entity().add_component<malt::material>();
    phong_material->set_ambient(glm::vec3(0.1f, 0.1f, 0.1f));
    phong_material->set_diffuse(glm::vec3(0.2f, 0.4f, 0.6f));
    phong_material->set_specular(glm::vec3(0.5f, 0.5f, 0.5f));
    phong_material->set_phong_exponent(32.0f);

    auto mesh_rend = get_entity().add_component<malt::mesh_renderer>();

    auto m = new rtk::gl::mesh(std::move(*malt::asset::load<rtk::gl::mesh>("models/teapot.obj")));
    mesh_rend->set_mesh(*m);

    auto texture = malt::asset::load<rtk::graphics::texture2d>("test.jpg");
    auto gl_texture = new rtk::gl::texture2d(*texture);

    gl_texture->activate(1);
    phong_material->get_shader().set_variable("tex", 1);

    malt::destroy(this);
}

MALT_IMPLEMENT_COMP(render_test)