//
// Created by fatih on 5/6/17.
//

#pragma once

#include <rtk/window.hpp>

namespace malt
{
    class display
    {
        const rtk::window* m_win;

    public:
        display(const rtk::window* w) : m_win(w) {};
        rtk::resolution get_resolution() const { return m_win->get_resolution(); }
    };
}



