#include <iostream>

#include <catch2/catch_test_macros.hpp>

#include "chessbot/CBoard.h"

TEST_CASE("Getting a bitboard") {
    CBoard board = CBoard("8/8/8/8/8/8/8/K6k w - - 0 1");

    CHECK(board.getPieceSet(enumPiece::nKing) == 9295429630892703744ULL);
    CHECK(board.getPieceSet(enumPiece::nWhite) == 72057594037927936ULL);
    CHECK(board.getPieceSet(enumPiece::nKing, enumPiece::nWhite) == 72057594037927936ULL);
}

TEST_CASE("Manipulating a square") {
    CBoard board = CBoard("k7/8/8/8/8/8/8/7K b - - 0 1");

    CHECK(board.getSquare(enumPiece::nBlack, enumSquare::a8));
    board.unsetSquare(enumPiece::nBlack, enumSquare::a8);
    CHECK(!board.getSquare(enumPiece::nBlack, enumSquare::a8));
    board.unsetSquare(enumPiece::nBlack, enumSquare::a8);
    CHECK(!board.getSquare(enumPiece::nBlack, enumSquare::a8));
    board.setSquare(enumPiece::nBlack, enumSquare::a8);
    CHECK(board.getSquare(enumPiece::nBlack, enumSquare::a8));
}
