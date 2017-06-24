//
// Created by fatih on 4/30/17.
//

#ifndef MALT_MESH_RENDERER_HPP
#define MALT_MESH_RENDERER_HPP

#include <malt_render/messages.hpp>
#include <malt_render/components/material.hpp>
#include <malt/component.hpp>
#include <rtk/gl/mesh.hpp>
#include <malt_render/render_ctx.hpp>

class mesh_renderer : public malt::component
{
    rtk::gl::mesh* m_mesh;
public:
    void set_mesh(rtk::gl::mesh& m);
    rtk::gl::mesh* get_mesh() { return m_mesh; }
    material* get_material() { return get_component<material>(); }

    void Handle(render, const render_ctx&);

    REFLECT(mesh_renderer, NOMEM);
};

#endif //MALT_MESH_RENDERER_HPP
