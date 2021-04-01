cmake_minimum_required(VERSION 3.8)

project(ISIM_tp1
    VERSION 1.0.0
    DESCRIPTION "Basic raytracer"
    LANGUAGES CXX
)
# Load custom cmake modules
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE Debug)
endif()

# create SOURCE_LIB static library: user souce library
add_subdirectory(src)
add_subdirectory(sdl)

if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
    # add test folder
    enable_testing()
    add_subdirectory(test)
endif()

# final binary output
add_executable(${PROJECT_NAME} src/main.cc)
target_compile_features(${PROJECT_NAME} PRIVATE
    cxx_std_17
)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC
    SOURCE_LIB
)
