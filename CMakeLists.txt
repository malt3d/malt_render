cmake_minimum_required(VERSION 3.5)
project(malt)

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake/")
set(CMAKE_CXX_STANDARD 14)

message(STATUS "${CMAKE_PREFIX_PATH}")

find_package(rtk REQUIRED)
find_package(SOIL REQUIRED)

include(Malt)

message(STATUS "${CMAKE_CXX_COMPILER_ID}")
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set(CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS} -undefined dynamic_lookup")
endif()

set(HEADER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include/malt_render")
set(HEADER_FILES
        ${HEADER_PATH}/render_global.hpp
        ${HEADER_PATH}/messages.hpp
        ${HEADER_PATH}/components/mesh_renderer.hpp
        ${HEADER_PATH}/components/render_test.hpp
        ${HEADER_PATH}/components/lights/directional_light.hpp
        ${HEADER_PATH}/components/lights/point_light.hpp
        ${HEADER_PATH}/components/camera.hpp
        ${HEADER_PATH}/components/material.hpp
        ${HEADER_PATH}/render_ctx.hpp
        ${HEADER_PATH}/texture/tex2d.hpp
        ${HEADER_PATH}/module.hpp
        ${HEADER_PATH}/display.hpp
        ${HEADER_PATH}/malt_render_fwd.hpp)

set(SOURCE_FILES
        components/mesh_renderer.cpp
        module.cpp
        render_global.cpp
        components/material.cpp
        components/render_test.cpp
        components/lights/directional_light.cpp
        components/lights/point_light.cpp
        components/camera.cpp
        texture/tex2d.cpp
        display.cpp)

add_library(malt_render SHARED ${SOURCE_FILES} ${HEADER_FILES})
malt_def_module(malt_render)

target_link_libraries(malt_render PUBLIC rtk)

target_include_directories(malt_render PUBLIC "${SOIL_INCLUDE_DIR}")
target_link_libraries(malt_render PUBLIC "${SOIL_LIBRARY}")

target_compile_definitions(malt_render PUBLIC GLM_ENABLE_EXPERIMENTAL=1)

malt_add_module(malt_render malt_core)
malt_add_module(malt_render malt_basic)

malt_install(malt_render ${HEADER_PATH})
