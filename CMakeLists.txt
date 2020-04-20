cmake_minimum_required(VERSION 3.13)

project(CockTorrent)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(src/include)

file(GLOB SOURCES "src/*.cpp")
add_executable(CockTorrent ${SOURCES})