cmake_minimum_required(VERSION 3.10)

project(ZMQDemo CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -ffast-math")

set(ZMQ_BUILD_TESTS OFF CACHE BOOL "Build ZMQ tests")
add_subdirectory(lib/libzmq)
set(CPPZMQ_BUILD_TESTS OFF CACHE BOOL "Build CPPZMQ tests")
add_subdirectory(lib/cppzmq)

add_executable(demo demo.cc)
target_link_libraries(demo PRIVATE libzmq cppzmq)
