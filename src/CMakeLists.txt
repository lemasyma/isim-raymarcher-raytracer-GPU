# Find libraries
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(Boost COMPONENTS program_options REQUIRED)

# Eventually do library handling if release or not
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(Boost_USE_STATIC_LIBS ON)
endif()

# Add your source files here
add_library(SOURCE_LIB STATIC
        scene/camera.hh scene/camera.cc
        scene/scene.hh scene/scene.cc
        scene/material/textureMaterial.hh
        scene/material/uniformTexture.hh
        scene/material/texture.hh
        scene/material/checkeredPatternTexture.hh

        scene/objects/object.hh
        scene/objects/sphere.hh
        scene/objects/capsule.hh
        scene/objects/torus.hh
        scene/objects/cube.hh
        scene/objects/cylinder.hh
        scene/objects/plane.hh

        scene/objects/operators/subtraction.hh
        scene/objects/operators/intersection.hh
        scene/objects/operators/union.hh

        scene/light/light.hh scene/light/pointLight.hh
        types/ray.hh types/pointn.hxx scene/pointIntensityComputer.hh
        scene/rayCaster.hh scene/rayCaster.cc
        )

# add important compile features
target_compile_features(SOURCE_LIB PRIVATE
    cxx_std_17
)

target_compile_options(SOURCE_LIB PRIVATE
    "-Wall"
    "-Wextra"
    $<$<CONFIG:Release>:-Werror -Wextra -Wall -Ofast -g0 -flto -march=native -fno-stack-protector
        -ffp-contract=off>
    $<$<CONFIG:Debug>:-O0 -g3>
    "-pedantic"
)

# link library to my files (ex: -lm for math utilities)
target_link_libraries(SOURCE_LIB
    ${Boost_LIBRARIES}
    Threads::Threads
)

# This is gcc's -I option for simple #include<> directive
# we also want to do it for libraries (better system compatibilities)
target_include_directories(SOURCE_LIB PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Boost_INCLUDE_DIR}
)
