cmake_minimum_required(VERSION 3.22)

project(OMPExamples LANGUAGES CXX)

find_package(OpenMP REQUIRED)

add_executable(simple_omp simple_omp.cpp)
target_link_libraries(simple_omp PRIVATE OpenMP::OpenMP_CXX)

add_executable(vector_omp vector_omp.cpp)
target_link_libraries(vector_omp PRIVATE OpenMP::OpenMP_CXX)

add_executable(vector_omp_simd vector_omp_simd.cpp)
target_link_libraries(vector_omp_simd PRIVATE OpenMP::OpenMP_CXX)

add_executable(vector_omp_large vector_omp_large.cpp)
target_link_libraries(vector_omp_large PRIVATE OpenMP::OpenMP_CXX)
