find_package(Vulkan REQUIRED)

#function(add_shaders TARGET_NAME)
#  set(SHADER_SOURCE_FILES ${ARGN}) # remainder of arguments are file list
#  message("target name: " ${TARGET_NAME})
#  message("shader source files: " ${SHADER_SOURCE_FILES})
#  # Validate source files
#  list(LENGTH SHADER_SOURCE_FILES FILE_COUNT)
#  if (FILE_COUNT EQUAL 0)
#    message(FATAL_ERROR "Cannot create a shaders target without any source files")
#  endif()
#
#  set(SHADER_COMMAND)
#  set(SHADER_PRODUCTS)
#
#  foreach(SHADER_SOURCE IN LISTS SHADER_SOURCE_FILES)
#    cmake_path(ABSOLUTE_PATH SHADER_SOURCE NORMALIZE)
#    cmake_path(GET SHADER_SOURCE FILENAME SHADER_NAME)
#
#    # Build command
#    list(APPEND SHADER_COMMAND COMMAND)
#    list(APPEND SHADER_COMMAND Vulkan::glslc)
#    list(APPEND SHADER_COMMAND "${SHADER_SOURCE}")
#    list(APPEND SHADER_COMMAND "-o")
#    list(APPEND SHADER_COMMAND "${CMAKE_CURRENT_BINARY_DIR}/${SHADER_NAME}.spv")
# 
#    # Add project
#    list(APPEND SHADER_PRODUCTS "${CMAKE_CURRENT_BINARY_DIR}/${SHADER_NAME}.spv")
#
#  endforeach()
#
#    add_custom_target(${TARGET_NAME} ALL
#      ${SHADER_COMMAND}
#      COMMENT "Compiling Shaders [${TARGET_NAME}]"
#      SOURCES ${SHADER_SOURCE_FILES}
#      BYPRODUCTS ${SHADER_PRODUCTS}
#      )
#endfunction()

add_shaders(${PROJECT_NAME} hello.frag)

