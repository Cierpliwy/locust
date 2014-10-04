cmake_minimum_required(VERSION 2.8)

project(locustcli)

find_package(Locust REQUIRED)
include_directories("${Locust_INCLUDE_DIRS}")

add_definitions(-std=c++11)

file(GLOB LOCUST_CLI_SRCS src/*.cpp)
add_executable(locust-cli ${LOCUST_CLI_SRCS})
target_link_libraries(locust-cli locust)
