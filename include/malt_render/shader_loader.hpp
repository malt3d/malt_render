//
// Created by Mehmet Fatih BAKIR on 16/05/2017.
//
#pragma once

#include <malt_asset/asset_file.hpp>
#include <malt/meta.hpp>
#include <rtk/rtk_fwd.hpp>

namespace malt
{
class shader_loader
{
public:
    using types = meta::list<rtk::gl::program>;

    bool check(meta::type<rtk::gl::program>, const asset::asset_file&) const;
    rtk::gl::program load(meta::type<rtk::gl::program>, asset::asset_file&);
};
}

