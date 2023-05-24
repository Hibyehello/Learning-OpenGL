cmake_minimum_required(VERSION 3.2)

project(cpp-app)

set (CMAKE_CXX_STANDARD 20)

find_package( OpenGL REQUIRED )

set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )

add_compile_definitions(GL_SILENCE_DEPRECATION) #Silence Deprecation warnings on MacOS

# 3rd Party libs
add_subdirectory(Vendor/glad2)
include_directories(Vendor/glad2/include)
add_subdirectory(Vendor/GLFW)
include_directories(Vendor/GLFW/include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

# Our Application folders
add_subdirectory(Source)
