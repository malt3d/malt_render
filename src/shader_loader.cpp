//
// Created by Mehmet Fatih BAKIR on 16/05/2017.
//

#include <malt_render/shader_loader.hpp>
#include <rtk/gl/program.hpp>
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <malt_asset/text_asset.hpp>
#include <malt_asset/assets.hpp>
#include <boost/filesystem.hpp>
#include <rtk/gl/shader.hpp>

namespace malt {
    using namespace YAML;
    bool shader_loader::check(meta::type<rtk::gl::program>, const asset::asset_file&) const
    {
        return true;
    }

    rtk::gl::program shader_loader::load(meta::type<rtk::gl::program>, asset::asset_file& f)
    {
        boost::filesystem::path fsp(f.get_path());
        std::cout << fsp << '\n';

        Node root = YAML::Load(f.get_stream());
        std::cerr << "Loading shader: " << root["shader"]["name"].as<std::string>() << '\n';

        auto vs_file = root["shader"]["vertex_shader"].as<std::string>();
        auto fs_file = root["shader"]["fragment_shader"].as<std::string>();

        auto vert_src = malt::asset::load<malt::text_asset>((fsp.parent_path() / vs_file).string());
        auto frag_src = malt::asset::load<malt::text_asset>((fsp.parent_path() / fs_file).string());

        rtk::gl::vertex_shader v_shader { vert_src.c_str() };
        rtk::gl::fragment_shader f_shader { frag_src.c_str() };

        rtk::gl::program program;
        program.attach(v_shader);
        program.attach(f_shader);
        program.link();

        return program;
    }
}
