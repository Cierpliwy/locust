cmake_minimum_required(VERSION 2.8)

project(locust)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)

add_subdirectory(lib)
add_subdirectory(test)
add_subdirectory(cli)
add_subdirectory(gui)
