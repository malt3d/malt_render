//
// Created by fatih on 3/1/18.
//

#pragma once

#include <malt/component.hpp>

class cube_test : public malt::component
{
public:
    void Handle(malt::start);
    REFLECT(cube_test, NOMEM);
};
