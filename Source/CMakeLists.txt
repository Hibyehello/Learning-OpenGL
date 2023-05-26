add_subdirectory(Core)

add_custom_target(copy-shader-files ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Source/Shaders ${CMAKE_BINARY_DIR}/out/Shaders DEPENDS ${MY_TARGET})

add_custom_target(copy-resource-files ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Source/Resources ${CMAKE_BINARY_DIR}/out/Resources DEPENDS ${MY_TARGET})
