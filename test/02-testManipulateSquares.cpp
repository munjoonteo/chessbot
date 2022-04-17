#include <iostream>

#include <catch2/catch_test_macros.hpp>

#include "chessbot/CBoard.h"

TEST_CASE("Getting a bitboard") {
    CBoard board = CBoard("8/8/8/8/8/8/8/K6k w - - 0 1");

    CHECK(board.getPieceSet(enumPiece::nKing) == 9295429630892703744);
    CHECK(board.getPieceSet(enumPiece::nWhite) == 72057594037927936);
    CHECK(board.getPieceSet(enumPiece::nKing, enumPiece::nWhite) == 72057594037927936);
}
