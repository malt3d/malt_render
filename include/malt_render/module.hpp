//
// Created by fatih on 4/30/17.
//

#pragma once

#include <malt/meta.hpp>

namespace malt
{
    class mesh_renderer;
    class material;
}

struct render_module_def
{
    using components = malt::meta::list<malt::mesh_renderer, malt::material, class render_test,
            class directional_light, class point_light, class camera, class cube_test>;

    using globals = malt::meta::list<class render_global>;

    using loaders = malt::meta::list<class mesh_loader, class shader_loader, class texture_loader>;
};

