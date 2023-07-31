cmake_minimum_required(VERSION 3.20)

add_executable(python_basics python_basics.cpp)
include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(python_basics ${PYTHON_LIBRARIES})
