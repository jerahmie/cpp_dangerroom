add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE vendor
        ${OPENGL_LIBRARIES})
add_shaders(triangle_shaders triangle.vert triangle.frag)

if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_BINARY_DIR}/vendor/SDL/SDL3.dll $<TARGET_FILE_DIR:${PROJECT_NAME}> 
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_BINARY_DIR}/vendor/SDL_image/SDL3_image.dll $<TARGET_FILE_DIR:${PROJECT_NAME}> 
    VERBATIM
    )
endif()
