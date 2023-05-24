add_subdirectory(Core)

add_custom_target(copy-runtime-files ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Source/Shaders ${CMAKE_BINARY_DIR}/out/Shaders DEPENDS ${MY_TARGET})
