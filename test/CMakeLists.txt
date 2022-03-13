project(ChessBot)

add_executable(main main.cpp)
target_link_libraries(main chessbot)
add_test(main main)