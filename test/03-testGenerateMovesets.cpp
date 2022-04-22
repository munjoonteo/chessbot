#include <iostream>

#include <catch2/catch_test_macros.hpp>

#include "chessbot/CBoard.h"

TEST_CASE("Getting Knight movesets") {
    CBoard board = CBoard();

    const Movesets* knightMovesets = board.getKnightMovesets();

    CHECK(1==1);
}

TEST_CASE("Getting King movesets") {
    CBoard board = CBoard();

    const Movesets* kingMovesets = board.getKingMovesets();

    // Bottom left corner
    U64 BLcornerBB = 0ULL;
    BLcornerBB = board.setSquare(BLcornerBB, enumSquare::a2);
    BLcornerBB = board.setSquare(BLcornerBB, enumSquare::b1);
    BLcornerBB = board.setSquare(BLcornerBB, enumSquare::b2);
    board.printBB(kingMovesets->at(enumSquare::a1));
    CHECK(kingMovesets->at(enumSquare::a1) == BLcornerBB);

    // Bottom right corner
    U64 BRcornerBB = 0ULL;
    BRcornerBB = board.setSquare(BRcornerBB, enumSquare::h2);
    BRcornerBB = board.setSquare(BRcornerBB, enumSquare::g1);
    BRcornerBB = board.setSquare(BRcornerBB, enumSquare::g2);
    board.printBB(kingMovesets->at(enumSquare::h1));
    CHECK(kingMovesets->at(enumSquare::h1) == BRcornerBB);

    // Top left corner
    U64 TLcornerBB = 0ULL;
    TLcornerBB = board.setSquare(TLcornerBB, enumSquare::a7);
    TLcornerBB = board.setSquare(TLcornerBB, enumSquare::b8);
    TLcornerBB = board.setSquare(TLcornerBB, enumSquare::b7);
    board.printBB(kingMovesets->at(enumSquare::a8));
    CHECK(kingMovesets->at(enumSquare::a8) == TLcornerBB);

    // Top right corner
    U64 TRcornerBB = 0ULL;
    TRcornerBB = board.setSquare(TRcornerBB, enumSquare::h7);
    TRcornerBB = board.setSquare(TRcornerBB, enumSquare::g8);
    TRcornerBB = board.setSquare(TRcornerBB, enumSquare::g7);
    board.printBB(kingMovesets->at(enumSquare::h8));
    CHECK(kingMovesets->at(enumSquare::h8) == TRcornerBB);
}