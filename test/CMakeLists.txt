project(ChessBot)

find_package(Catch2 REQUIRED)

add_executable(main main.cpp)
target_link_libraries(main Catch2::Catch2WithMain)

add_executable(AllTests 01-testBoardCreate.cpp)
target_link_libraries( AllTests Catch2::Catch2WithMain )
target_link_libraries( AllTests chessbot )

include(Catch)
catch_discover_tests(AllTests)
