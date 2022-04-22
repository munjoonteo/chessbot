cmake_minimum_required(VERSION 3.15)

project(ChessBot)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED)
set(CMAKE_CXX_FLAGS "-Wall -Wpedantic -std=c++2a -O3")
set(CMAKE_OSX_DEPLOYMENT_TARGET 12)

enable_testing()

include_directories(include)
add_subdirectory(src)
add_subdirectory(test)
