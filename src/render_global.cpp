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
#include <malt_basic/input.hpp>
#include <rtk/framebuffer.hpp>
#include <malt/strided_iterator.hpp>
#include <rtk/gl/program.hpp>
#include <malt_asset/assets.hpp>
#include <rtk/texture/tex2d.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

using namespace rtk;

static render_mod* inst;

namespace malt
{
namespace input
{
    bool get_key_up(key_code code)
    {
        return inst->w->get_key_up(uint16_t(code));
    }

    bool get_key_down(key_code code)
    {
        return inst->w->get_key_down(uint16_t(code));
    }

    glm::vec2 get_cursor()
    {
        return inst->w->get_mouse();
    }
}
}

std::shared_ptr<rtk::gl::program> shadow_prog;

void render_mod::init()
{
    using namespace rtk::literals;
    w = new window({800_px, 600_px}, "malt");
    //w->lock_cursor(true);
    inst = this;
    shadow_prog = malt::asset::load<rtk::gl::program>("malt_shaders/shadow.s.yml");
}

void render_mod::destruct()
{
    shadow_prog.reset();
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

    using namespace rtk::literals;
    static rtk::gl::texture2d out = rtk::gl::create_texture(rtk::resolution(1024_px, 1024_px), rtk::graphics::pixel_format::gl_depth16);
    out.activate(0);
    static rtk::gl::framebuffer shadow_buf(out);

    for (auto& plight : malt::get_components<point_light>())
    {
        pl[pl_len].position = plight.get_component<malt::transform>()->get_pos();
        pl[pl_len].intensity = plight.get_intensity();
        ++pl_len;
    }

    for (directional_light& dlight : malt::get_components<directional_light>())
    {
        dl.direction = dlight.get_light_direction();
        dl.intensity = dlight.get_intensity();
    }

    for(camera& cam : malt::get_components<camera>())
    {
        shadow_ctx sctx;
        glm::mat4 dpm = glm::ortho<float>(-10, 10, -10, 10, 0.1f, 100);
        glm::mat4 dvm = glm::lookAt(glm::vec3(-5, 5, -5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        sctx.depth_mvp = dpm * dvm;
        sctx.mat = shadow_prog.get();
        pl[0].transform = sctx.depth_mvp;
        glViewport(0, 0, 1024, 1024);
        shadow_buf.activate_depth();
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glClear(GL_DEPTH_BUFFER_BIT);
        malt::broadcast(shadow{}, sctx);
        /*auto dep = read_depth(out);
        for (int i = 0; i < 1024; ++i)
        {
            for (int j = 0; j < 1024; ++j)
            {
                auto p = ((float*)dep.m_data)[i * 1024 + j];
                if (p != 1)
                    std::cout << p << '\n';
            }
        }*/

        gl::reset_framebuffer();
        render_ctx ctx;
        ctx.vp = cam.get_vp_matrix();
        ctx.cam_position = cam.get_component<malt::transform>()->get_pos();
        ctx.ambient_light = ambient;
        ctx.point_light_size = pl_len;
        ctx.dir_light = dl;
        ctx.shadow = &out;
        std::copy(std::begin(pl), std::end(pl), std::begin(ctx.point_lights));

        malt::display d(w);
        cam.set_display(&d);
        cam.activate();

        malt::broadcast(render{}, ctx);

        gl::reset_framebuffer();
    }

    w->end_draw();
}
