//
// Created by fatih on 5/18/17.
//

#pragma once

#include <malt/meta.hpp>
#include <rtk/rtk_fwd.hpp>
#include <malt_asset/asset_file.hpp>

namespace malt
{
class texture_loader
{
public:
    using types = meta::list<rtk::graphics::texture2d, rtk::gl::texture2d>;

    bool check(meta::type<rtk::graphics::texture2d>, const asset::asset_file&);
    rtk::graphics::texture2d load(meta::type<rtk::graphics::texture2d>, asset::asset_file&);

    bool check(meta::type<rtk::gl::texture2d>, const asset::asset_file&);
    rtk::gl::texture2d load(meta::type<rtk::gl::texture2d>, asset::asset_file&);
private:
};
}


