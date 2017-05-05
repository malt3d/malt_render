//
// Created by fatih on 4/30/17.
//

#include <malt_render/components/mesh_renderer.hpp>
#include <malt_render/components/material.hpp>
#include <rtk/gl/mesh.hpp>
#include <malt/component_mgr_impl.hpp>
#include <malt_basic/components/transform.hpp>

void mesh_renderer::Handle(render, const render_ctx& ctx)
{
    auto mat = get_entity().get_component<material>();
    auto& prog = mat->get_program();
    prog.set_variable("model", get_component<malt::transform>()->get_mat4());
    prog.set_variable("vp", ctx.vp);
    prog.set_variable("camera_position", ctx.cam_position);
    prog.set_variable("ambient_light", ctx.ambient_light);
    prog.set_variable("directional_light.intensity", ctx.dir_light.intensity);
    prog.set_variable("directional_light.direction", ctx.dir_light.direction);
    prog.set_variable("number_of_point_lights", 0);
    m_mesh->draw(prog);
}

void mesh_renderer::set_mesh(rtk::gl::mesh& m)
{
    m_mesh = &m;
}

MALT_IMPLEMENT_COMP(mesh_renderer)