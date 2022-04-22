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
    board.setSquare(&BLcornerBB, enumSquare::a2);
    board.setSquare(&BLcornerBB, enumSquare::b1);
    board.setSquare(&BLcornerBB, enumSquare::b2);
    board.printBB(kingMovesets->at(enumSquare::a1));
    CHECK(kingMovesets->at(enumSquare::a1) == BLcornerBB);

    // Bottom right corner
    U64 BRcornerBB = 0ULL;
    board.setSquare(&BRcornerBB, enumSquare::h2);
    board.setSquare(&BRcornerBB, enumSquare::g1);
    board.setSquare(&BRcornerBB, enumSquare::g2);
    board.printBB(kingMovesets->at(enumSquare::h1));
    CHECK(kingMovesets->at(enumSquare::h1) == BRcornerBB);

    // Top left corner
    U64 TLcornerBB = 0ULL;
    board.setSquare(&TLcornerBB, enumSquare::a7);
    board.setSquare(&TLcornerBB, enumSquare::b8);
    board.setSquare(&TLcornerBB, enumSquare::b7);
    board.printBB(kingMovesets->at(enumSquare::a8));
    CHECK(kingMovesets->at(enumSquare::a8) == TLcornerBB);

    // Top right corner
    U64 TRcornerBB = 0ULL;
    board.setSquare(&TRcornerBB, enumSquare::h7);
    board.setSquare(&TRcornerBB, enumSquare::g8);
    board.setSquare(&TRcornerBB, enumSquare::g7);
    board.printBB(kingMovesets->at(enumSquare::h8));
    CHECK(kingMovesets->at(enumSquare::h8) == TRcornerBB);

    // Top edge
    U64 topEdgeBB = 0ULL;
    board.setSquare(&topEdgeBB, enumSquare::c8);
    board.setSquare(&topEdgeBB, enumSquare::c7);
    board.setSquare(&topEdgeBB, enumSquare::d7);
    board.setSquare(&topEdgeBB, enumSquare::e7);
    board.setSquare(&topEdgeBB, enumSquare::e8);
    board.printBB(kingMovesets->at(enumSquare::d8));
    CHECK(kingMovesets->at(enumSquare::d8) == topEdgeBB);

    // Right edge
    U64 rightEdgeBB = 0ULL;
    board.setSquare(&rightEdgeBB, enumSquare::h5);
    board.setSquare(&rightEdgeBB, enumSquare::g5);
    board.setSquare(&rightEdgeBB, enumSquare::g4);
    board.setSquare(&rightEdgeBB, enumSquare::g3);
    board.setSquare(&rightEdgeBB, enumSquare::h3);
    board.printBB(kingMovesets->at(enumSquare::h4));
    CHECK(kingMovesets->at(enumSquare::h4) == rightEdgeBB);

    // Bottom edge
    U64 bottomEdgeBB = 0ULL;
    board.setSquare(&bottomEdgeBB, enumSquare::c1);
    board.setSquare(&bottomEdgeBB, enumSquare::c2);
    board.setSquare(&bottomEdgeBB, enumSquare::d2);
    board.setSquare(&bottomEdgeBB, enumSquare::e2);
    board.setSquare(&bottomEdgeBB, enumSquare::e1);
    board.printBB(kingMovesets->at(enumSquare::d1));
    CHECK(kingMovesets->at(enumSquare::d1) == bottomEdgeBB);

    // Left edge
    U64 leftEdgeBB = 0ULL;
    board.setSquare(&leftEdgeBB, enumSquare::a5);
    board.setSquare(&leftEdgeBB, enumSquare::b5);
    board.setSquare(&leftEdgeBB, enumSquare::b4);
    board.setSquare(&leftEdgeBB, enumSquare::b3);
    board.setSquare(&leftEdgeBB, enumSquare::a3);
    board.printBB(kingMovesets->at(enumSquare::a4));
    CHECK(kingMovesets->at(enumSquare::a4) == leftEdgeBB);

    // Center
    U64 centerBB = 0ULL;
    board.setSquare(&centerBB, enumSquare::d5);
    board.setSquare(&centerBB, enumSquare::e5);
    board.setSquare(&centerBB, enumSquare::e4);
    board.setSquare(&centerBB, enumSquare::e3);
    board.setSquare(&centerBB, enumSquare::d3);
    board.setSquare(&centerBB, enumSquare::c3);
    board.setSquare(&centerBB, enumSquare::c4);
    board.setSquare(&centerBB, enumSquare::c5);
    board.printBB(kingMovesets->at(enumSquare::d4));
    CHECK(kingMovesets->at(enumSquare::d4) == centerBB);
}