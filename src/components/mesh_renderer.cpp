//
// Created by fatih on 4/30/17.
//

#include <malt_render/components/mesh_renderer.hpp>
#include <malt_render/components/material.hpp>
#include <rtk/gl/mesh.hpp>
#include <malt/detail/component_mgr_impl.hpp>
#include <malt_basic/components/transform.hpp>
#include <rtk/texture/tex2d.hpp>

namespace malt
{
    void mesh_renderer::Handle(render, const render_ctx& ctx)
    {
        auto mat = get_material();
        auto& prog = mat->get_shader();
        prog.set_variable("model", get_component<malt::transform>()->get_world_mat4());
        prog.set_variable("vp", ctx.vp);
        prog.set_variable("camera_position", ctx.cam_position);
        prog.set_variable("ambient_light", ctx.ambient_light);
        prog.set_variable("directional_light.intensity", ctx.dir_light.intensity);
        prog.set_variable("directional_light.direction", ctx.dir_light.direction);
        prog.set_variable("number_of_point_lights", ctx.point_light_size);
        prog.set_variable("shadowTex", 0);
        prog.set_variable("lightMat", ctx.point_lights[0].transform);
        ctx.shadow->activate(0);
        for (int i = 0; i < ctx.point_light_size; ++i)
        {
            prog.set_variable("point_light[" + std::to_string(i) + "].intensity", ctx.point_lights[i].intensity);
            prog.set_variable("point_light[" + std::to_string(i) + "].position", ctx.point_lights[i].position);
        }
        m_mesh->draw(prog);
    }

    void mesh_renderer::Handle(shadow, const shadow_ctx& ctx)
    {
        auto& prog = *ctx.mat;
        prog.set_variable("model", get_component<malt::transform>()->get_world_mat4());
        prog.set_variable("vp", ctx.depth_mvp);
        m_mesh->draw(prog);
    }

    void mesh_renderer::set_mesh(rtk::gl::mesh& m)
    {
        m_mesh = &m;
    }

}

MALT_IMPLEMENT_COMP(malt::mesh_renderer)