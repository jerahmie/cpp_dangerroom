cmake_minimum_required(VERSION 3.22)
project(graphics)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenGL
find_package(OpenGL REQUIRED)

#set(STB_INCLUDE_DIR "/usr/include/stb")

include_directories( ${OPENGL_INCLUDE_DIR})

# Vendor includes SDL3
add_subdirectory(vendor)

add_subdirectory(sdl3_00_cmake)
add_subdirectory(sdl3_01_clear)
#add_subdirectory(sdl_gpu_00_dev_prop)
add_subdirectory(sdl3_02_blur)
add_subdirectory(sdl_gpu_01_triangle)

