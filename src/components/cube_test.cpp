//
// Created by fatih on 3/1/18.
//


#include <malt_render/components/cube_test.hpp>
#include <malt_render/components/material.hpp>
#include <malt_render/components/mesh_renderer.hpp>
#include <rtk/geometry/mesh.hpp>
#include <rtk/mesh_ops.hpp>

void cube_test::Handle(malt::start) {
    auto phong_material = get_entity().add_component<malt::material>();
    phong_material->set_ambient(glm::vec3(0.1f, 0.1f, 0.1f));
    phong_material->set_diffuse(glm::vec3(1.8, 1.8, 1.8));
    phong_material->set_specular(glm::vec3(0.5f, 0.5f, 0.5f));
    phong_material->set_phong_exponent(32.0f);

    auto mesh_rend = get_entity().add_component<malt::mesh_renderer>();

    auto mesh = rtk::geometry::primitive::cube();
    auto m = new rtk::gl::mesh(rtk::geometry::create(mesh));
    m->add_vertex_data<glm::vec3>(1, rtk::geometry::generate_normals(mesh));
    mesh_rend->set_mesh(*m);

    malt::destroy(this);
}
