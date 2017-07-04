//
// Created by fatih on 5/18/17.
//

#include <rtk/texture/tex2d.hpp>
#include <malt_render/texture_loader.hpp>
#include <SOIL/SOIL.h>
#include <malt_asset/asset_mgr.hpp>
#include <malt_asset/assets.hpp>

namespace malt
{
    bool texture_loader::check(meta::type<rtk::graphics::texture2d>, const asset::asset_file& f)
    {
        return true;
    }

    rtk::graphics::texture2d
    texture_loader::load(meta::type<rtk::graphics::texture2d>, asset::asset_file& f)
    {
        int w, h;
        auto im_data = std::make_unique<uint8_t[]>(f.get_size());
        f.get_stream().read((char*)im_data.get(), f.get_size());
        auto data = SOIL_load_image_from_memory(im_data.get(), f.get_size(), &w, &h, 0, SOIL_LOAD_RGB);
        if (data ==nullptr)
        {
            throw asset::loader_error("SOIL can't really load this :(");
        }
        auto vec3_data = std::make_unique<glm::vec3[]>(w * h);
        for (int i = 0; i < w * h * 3; i += 3)
        {
            vec3_data[i / 3] = glm::vec3(data[i], data[i + 1], data[i + 2]) / 255.f;
        }
        auto res = rtk::graphics::texture2d(std::move(vec3_data), rtk::resolution(rtk::pixels(w), rtk::pixels(h)));
        SOIL_free_image_data(data);
        return res;
    }

    bool texture_loader::check(meta::type<rtk::gl::texture2d>, const asset::asset_file&)
    {
        return true;
    }

    rtk::gl::texture2d texture_loader::load(meta::type<rtk::gl::texture2d>, asset::asset_file& f)
    {
        auto res = asset::load<rtk::graphics::texture2d>(f.get_path());
        return {*res};
    }


}

