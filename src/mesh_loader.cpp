//
// Created by fatih on 5/16/17.
//

#include <malt_render/mesh_loader.hpp>
#include <rtk/geometry/mesh.hpp>
#include <rtk/gl/mesh.hpp>
#include <rtk/asset/mesh_import.hpp>
#include <malt_asset/assets.hpp>
#include <rtk/mesh_ops.hpp>
#include <glm/glm.hpp>

namespace malt
{
bool mesh_loader::check(meta::type<rtk::geometry::mesh>, const asset::asset_file&) const
{
    return true;
}

rtk::geometry::mesh mesh_loader::load(meta::type<rtk::geometry::mesh>, asset::asset_file& f)
{
    auto& stream = f.get_stream();
    auto size = f.get_size();

    std::vector<uint8_t> buffer(size);
    stream.read((char*)buffer.data(), size);

    auto res = rtk::assets::load_meshes((char*)buffer.data(), buffer.size());
    return res[0];
}

bool mesh_loader::check(meta::type<rtk::gl::mesh>, const asset::asset_file&) const
{
    return true;
}

rtk::gl::mesh mesh_loader::load(meta::type<rtk::gl::mesh>, asset::asset_file& f)
{
    auto geo_mesh = malt::asset::load<rtk::geometry::mesh>(f.get_path());
    auto m = create(*geo_mesh);
    m.add_vertex_data<glm::vec3>(1, rtk::geometry::generate_normals(*geo_mesh));
    return m;
}
}

