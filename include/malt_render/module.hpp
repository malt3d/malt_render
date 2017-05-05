//
// Created by fatih on 4/30/17.
//

#pragma once

#include <malt/list.hpp>

struct render_module_def
{
    using components = malt::mp::list<class mesh_renderer, class material, class render_test,
            class directional_light, class point_light, class camera>;
};

