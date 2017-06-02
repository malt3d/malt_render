cmake_minimum_required(VERSION 3.5)
project(malt)

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../malt_cmake/")
set(CMAKE_CXX_STANDARD 14)

message(STATUS "${CMAKE_PREFIX_PATH}")

find_package(rtk REQUIRED)
find_package(SOIL REQUIRED)
find_package(glm REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem)

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
        ${HEADER_PATH}/module.hpp
        ${HEADER_PATH}/display.hpp
        ${HEADER_PATH}/render_fwd.hpp
        ${HEADER_PATH}/shader_loader.hpp
        ${HEADER_PATH}/texture_loader.hpp
        ${HEADER_PATH}/mesh_loader.hpp
        )

set(SOURCE_FILES
        src/components/mesh_renderer.cpp
        src/module.cpp
        src/render_global.cpp
        src/components/material.cpp
        src/components/render_test.cpp
        src/components/lights/directional_light.cpp
        src/components/lights/point_light.cpp
        src/components/camera.cpp
        src/display.cpp
        src/shader_loader.cpp
        src/mesh_loader.cpp
        src/texture_loader.cpp
        )

add_library(malt_render ${MALT_LIB_TYPE} ${SOURCE_FILES} ${HEADER_FILES})
malt_def_module(malt_render)

target_link_libraries(malt_render PUBLIC rtk)

target_include_directories(malt_render PUBLIC "${SOIL_INCLUDE_DIR}")
target_include_directories(malt_render PUBLIC ${GLM_INCLUDE_DIR})
target_link_libraries(malt_render PUBLIC "${SOIL_LIBRARY}")
target_link_libraries(malt_render PUBLIC "${Boost_LIBRARIES}")

target_link_libraries(malt_render PUBLIC yaml-cpp)

target_compile_definitions(malt_render PUBLIC GLM_ENABLE_EXPERIMENTAL=1)

malt_add_module(malt_render malt_core)
malt_add_module(malt_render malt_basic)
malt_add_module(malt_render malt_asset)

malt_install(malt_render ${HEADER_PATH})
