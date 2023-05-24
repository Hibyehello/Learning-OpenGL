cmake_minimum_required(VERSION 3.2)
project(glad2)

add_library(glad2 include/glad/glad.h src/glad.c)
target_include_directories(glad2 PUBLIC include/)
