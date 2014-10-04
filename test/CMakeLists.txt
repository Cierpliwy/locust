cmake_minimum_required(VERSION 2.8)

project(locusttest)

find_package(Locust REQUIRED)
include_directories("${Locust_INCLUDE_DIRS}")

add_definitions(-std=c++11)

file(GLOB LOCUST_TEST_SRCS *.cpp)
add_executable(locust-test ${LOCUST_TEST_SRCS})
target_link_libraries(locust-test locust)
