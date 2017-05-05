//
// Created by fatih on 4/30/17.
//

#pragma once

#include <rtk/rtk_init.hpp>
#include <rtk/window.hpp>
#include <malt/engine.hpp>
#include "messages.hpp"

class render_mod
{
    rtk::rtk_init init_;
public:
    rtk::window* w;

    void init();

    void destruct();

    void update();
};
