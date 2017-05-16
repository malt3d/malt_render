//
// Created by Mehmet Fatih BAKIR on 16/05/2017.
//

#include <malt_render/shader_loader.hpp>

namespace malt {
    bool shader_loader::check(meta::type<rtk::gl::program>, const asset::asset_file&) const
    {
        return true;
    }

    rtk::gl::program shader_loader::load(meta::type<rtk::gl::program>, asset::asset_file& f)
    {

    }
}
