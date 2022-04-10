project(ChessBot)

add_library(chessbot CBoard.cpp)
target_include_directories(chessbot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)