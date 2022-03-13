cmake_minimum_required(VERSION 3.15)

project(ChessBot)

set(CMAKE_CXX_STANDARD 20)

enable_testing()
include(CTest)

include_directories(include)
add_subdirectory(src)
add_subdirectory(test)
