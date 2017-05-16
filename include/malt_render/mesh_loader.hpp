//
// Created by fatih on 5/16/17.
//

#pragma once

#include <malt/list.hpp>
#include <rtk/rtk_fwd.hpp>
#include <malt_asset/asset_loader.hpp>

namespace malt
{
class mesh_loader
{
public:
    using types = meta::list<rtk::geometry::mesh, rtk::gl::mesh>;

    bool check(meta::type<rtk::geometry::mesh>, const asset::asset_file&) const;
    bool check(meta::type<rtk::gl::mesh>, const asset::asset_file&) const;

    rtk::geometry::mesh load(meta::type<rtk::geometry::mesh>, asset::asset_file&);
    rtk::gl::mesh load(meta::type<rtk::gl::mesh>, asset::asset_file&);
};
}
