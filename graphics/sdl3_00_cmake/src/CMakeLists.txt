add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE vendor)
target_link_libraries(${PROJECT_NAME} PRIVATE vendor)

