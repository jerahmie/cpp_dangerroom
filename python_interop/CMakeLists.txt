cmake_minimum_required(VERSION 3.20)

project(python_interop)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(PythonLibs REQUIRED)
add_subdirectory(python_basics)
