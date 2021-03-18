cmake_minimum_required(VERSION 3.10)
project(Textured_cube VERSION 1.0)

# OpenGL
find_package(OpenGL REQUIRED)

# GLFW3
add_subdirectory(external/glfw-3.3.2)
include_directories(external/glfw-3.3.2/include)

# GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_PATH})

# STB_IMAGE
add_library(STB_IMAGE "external/stb/stb_image.cpp")

# libnoise
include(${CMAKE_SOURCE_DIR}/external/cmake-modules/LibNoiseConfig.cmake)
include_directories(${LIBNOISE_INCLUDE_PATH})



# add the executable
add_executable(Textured_cube
    src/main.cpp
    src/shader.cpp
    src/vertex_buffer.cpp
    src/vertex_array.cpp
    src/quad.cpp
    src/texture.cpp
    src/cube.cpp
    src/camera.cpp
    src/world/map.cpp
    src/world/biome.cpp
    src/world/renderer.cpp
)

target_include_directories(Textured_cube
    PRIVATE src/include    
)

target_link_libraries(Textured_cube PUBLIC 
    ${OPENGL_LIBRARY}
    ${GLEW_LIBRARY}
    glfw
    ${GLFW_LIBRARIES}
    STB_IMAGE
    noise
)


# Test
add_executable(map_test
    test/map_test.cpp
    src/world/map.cpp
)

target_include_directories(map_test
    PRIVATE src/include    
)

target_link_libraries(map_test PUBLIC 
    ${OPENGL_LIBRARY}
    ${GLEW_LIBRARY}
    glfw
    ${GLFW_LIBRARIES}
    STB_IMAGE
    noise
)