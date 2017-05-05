//
// Created by musti on 30.04.2017.
//

#ifndef MALT_RENDER_TEST_H
#define MALT_RENDER_TEST_H

#include <malt/component.hpp>
#include <rtk/gl/program.hpp>
#include <rtk/geometry/mesh.hpp>
#include <rtk/gl/mesh.hpp>
#include <malt_render/messages.hpp>

class render_test : public malt::component
{
public:
    void Handle(malt::start);
};


#endif //MALT_RENDER_TEST_H
