cmake_minimum_required(VERSION 3.20)

project(Hello)

#find_package(netCDF REQUIRED)
find_package(netCDFCxx CONFIG REQUIRED)
add_executable(Hello hello.cpp)

