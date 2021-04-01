find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

set(VIEWER_NAME "${PROJECT_NAME}_viewer")
add_executable(${VIEWER_NAME} main.cc)

target_compile_features(${VIEWER_NAME} PRIVATE
    cxx_std_17
)

include_directories(${VIEWER_NAME}
    ${SDL2_IMAGE_INCLUDE_DIRS}
)

target_link_libraries(${VIEWER_NAME} LINK_PUBLIC
    SOURCE_LIB SDL2::SDL2 ${SDL2_IMAGE_LIBRARIES}
)