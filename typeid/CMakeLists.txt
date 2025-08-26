cmake_minimum_required(VERSION 3.22)

project(Types_Test)

find_package(HDF5 COMPONENTS CXX HL)

include_directories(${HDF5_INCLUDE_DIRS})

add_executable(types_test types_test.cpp)
target_link_libraries(types_test ${HDF5_CXX_LIBRARIES})

add_executable(min_max_double min_max_double.cpp)
