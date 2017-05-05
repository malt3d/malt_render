//
// Created by fatih on 4/30/17.
//

#include <glm/glm.hpp>
#include <malt_render/render_global.hpp>
#include <malt_render/render_ctx.hpp>
#include <GLFW/glfw3.h>
#include <malt_render/components/camera.hpp>
#include <malt_basic/components/transform.hpp>
#include <malt_render/components/lights/point_light.hpp>
#include <malt_render/components/lights/directional_light.hpp>
#include <malt_render/display.hpp>

static render_mod* inst;

namespace malt
{
namespace input
{
    bool get_key(int keycode)
    {
        return inst->w->get_key(keycode);
    }

    bool get_key_up(int keycode)
    {
        return inst->w->get_key_up(keycode);
    }

    bool get_key_down(int keycode)
    {
        return inst->w->get_key_down(keycode);
    }

    glm::vec2 get_cursor()
    {
        return inst->w->get_mouse();
    }
}
}

void render_mod::init()
{
    using namespace rtk::literals;
    w = new rtk::window({800_px, 600_px}, "malt");
    w->lock_cursor(true);
    inst = this;
}

void render_mod::destruct()
{
    w->lock_cursor(false);
    delete w;
}

void render_mod::update()
{
    if (w->should_close())
    {
        malt::terminate();
        return;
    }
    w->begin_draw();

    glm::vec3 ambient = {1, 1, 1};
    directional_light_data dl;
    point_light_data pl[8];
    int pl_len = 0;

    malt::for_each_component<point_light>([&](point_light* p_pl)
    {
        pl[pl_len].position = p_pl->get_component<malt::transform>()->get_pos();
        pl[pl_len].intensity = p_pl->get_intensity();
        ++pl_len;
    });

    malt::for_each_component<directional_light>([&](directional_light* p_dl)
    {
        dl.direction = p_dl->get_light_direction();
        dl.intensity = p_dl->get_intensity();
    });

    malt::for_each_component<camera>([&](camera* cam)
    {
        render_ctx ctx;
        ctx.vp = cam->get_vp_matrix();
        ctx.cam_position = cam->get_component<malt::transform>()->get_pos();
        ctx.ambient_light = ambient;
        ctx.point_light_size = pl_len;
        ctx.dir_light = dl;
        std::copy(std::begin(pl), std::end(pl), std::begin(ctx.point_lights));

        malt::display d(w);
        cam->set_display(&d);
        cam->activate();

        malt::broadcast(render{}, ctx);
    });
    w->end_draw();
}
