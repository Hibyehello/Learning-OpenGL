cmake_minimum_required(VERSION 3.2)

project(cpp-app)

SET( CMAKE_EXPORT_COMPILE_COMMANDS ON )
set (CMAKE_CXX_STANDARD 20)

find_package( OpenGL REQUIRED )

set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )

add_compile_definitions(GL_SILENCE_DEPRECATION) #Silence Deprecation warnings on MacOS

IF( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" )
  EXECUTE_PROCESS( COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
  )
ENDIF()

# 3rd Party libs
add_subdirectory(Vendor/glad2)
include_directories(Vendor/glad2/include)
add_subdirectory(Vendor/GLFW)
include_directories(Vendor/GLFW/include)
add_subdirectory(Vendor/stb_image)
include_directories(Vendor/stb_image)
add_subdirectory(Vendor/glm)
include_directories(Vendor/glm)
add_subdirectory(Vendor/imgui)
include_directories(Vendor/imgui)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

# Our Application folders
include_directories(Source)
add_subdirectory(Source)
