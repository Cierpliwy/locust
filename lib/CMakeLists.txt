cmake_minimum_required(VERSION 2.8)

project(liblocust)

find_package(SQLite3 REQUIRED)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories("${SQLITE3_INCLUDE_DIRS}")

set(CMAKE_CXX_COMPILER clang++)
add_definitions("-std=c++11 -Weverything -Werror -Wno-c++98-compat -Wno-shadow -Wno-padded -Wno-weak-vtables")

file(GLOB_RECURSE LIBLOCUST_SRCS src/ *.cpp)

add_library(locust ${LIBLOCUST_SRCS})
target_link_libraries(locust ${SQLITE3_LIBRARIES})
