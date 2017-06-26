//
// Created by fatih on 4/30/17.
//

#pragma once

#include <malt/meta.hpp>

struct render_module_def
{
    using components = malt::meta::list<class mesh_renderer, class material, class render_test,
            class directional_light, class point_light, class camera>;

    using globals = malt::meta::list<class render_global>;

    using loaders = malt::meta::list<class mesh_loader, class shader_loader, class texture_loader>;
};

