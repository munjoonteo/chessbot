#include <iostream>

#include <catch2/catch_test_macros.hpp>

#include "chessbot/CBoard.h"

void setAndCheck(std::vector<enumSquare> *moves, CBoard* board, U64 *bb, enumSquare square, const Movesets* movesets) {
    for (auto move: *moves) board->setSquare(bb, move);
    board->printBB(movesets->at(square));
    CHECK(movesets->at(square) == *bb);
}

TEST_CASE("Getting Knight movesets") {
    CBoard board = CBoard();

    const Movesets* knightMovesets = board.getKnightMovesets();

    // Corners
    U64 a8 = 0ULL;
    std::vector<enumSquare> a8Moves = { c7, b6 };
    setAndCheck(&a8Moves, &board, &a8, enumSquare::a8, knightMovesets);

    U64 h8 = 0ULL;
    std::vector<enumSquare> h8Moves = { f7, g6 };
    setAndCheck(&h8Moves, &board, &h8, enumSquare::h8, knightMovesets);

    U64 a1 = 0ULL;
    std::vector<enumSquare> a1Moves = { c2, b3 };
    setAndCheck(&a1Moves, &board, &a1, enumSquare::a1, knightMovesets);

    U64 h1 = 0ULL;
    std::vector<enumSquare> h1Moves = { f2, g3 };
    setAndCheck(&h1Moves, &board, &h1, enumSquare::h1, knightMovesets);

    // Left and right edges
    U64 a7 = 0ULL;
    std::vector<enumSquare> a7Moves = { c8, c6, b5 };
    setAndCheck(&a7Moves, &board, &a7, enumSquare::a7, knightMovesets);

    U64 a6 = 0ULL;
    std::vector<enumSquare> a6Moves = { b8, c7, c5, b4 };
    setAndCheck(&a6Moves, &board, &a6, enumSquare::a6, knightMovesets);

    U64 h7 = 0ULL;
    std::vector<enumSquare> h7Moves = { f8, f6, g5 };
    setAndCheck(&h7Moves, &board, &h7, enumSquare::h7, knightMovesets);

    U64 h6 = 0ULL;
    std::vector<enumSquare> h6Moves = { g8, f7, f5, g4 };
    setAndCheck(&h6Moves, &board, &h6, enumSquare::h6, knightMovesets);

    // Center
    U64 e5 = 0ULL;
    std::vector<enumSquare> e5Moves = { d7, f7, g6, g4, f3, d3, c6, c4 };
    setAndCheck(&e5Moves, &board, &e5, enumSquare::e5, knightMovesets);
}

TEST_CASE("Getting King movesets") {
    CBoard board = CBoard();

    const Movesets* kingMovesets = board.getKingMovesets();

    // Corners
    U64 a1 = 0ULL;
    std::vector<enumSquare> a1Moves = { a2, b1, b2 };
    setAndCheck(&a1Moves, &board, &a1, enumSquare::a1, kingMovesets);

    U64 h1 = 0ULL;
    std::vector<enumSquare> h1Moves = { h2, g1, g2 };
    setAndCheck(&h1Moves, &board, &h1, enumSquare::h1, kingMovesets);

    U64 a8 = 0ULL;
    std::vector<enumSquare> a8Moves = { a7, b8, b7 };
    setAndCheck(&a8Moves, &board, &a8, enumSquare::a8, kingMovesets);

    U64 h8 = 0ULL;
    std::vector<enumSquare> h8Moves = { h7, g8, g7 };
    setAndCheck(&h8Moves, &board, &h8, enumSquare::h8, kingMovesets);

    // Edges
    U64 d8 = 0ULL;
    std::vector<enumSquare> d8Moves = { c8, c7, d7, e7, e8 };
    setAndCheck(&d8Moves, &board, &d8, enumSquare::d8, kingMovesets);

    U64 h4 = 0ULL;
    std::vector<enumSquare> h4Moves = { h5, g5, g4, g3, h3 };
    setAndCheck(&h4Moves, &board, &h4, enumSquare::h4, kingMovesets);

    U64 d1 = 0ULL;
    std::vector<enumSquare> d1Moves = { c1, c2, d2, e2, e1 };
    setAndCheck(&d1Moves, &board, &d1, enumSquare::d1, kingMovesets);

    U64 a4 = 0ULL;
    std::vector<enumSquare> a4Moves = { a5, b5, b4, b3, a3 };
    setAndCheck(&a4Moves, &board, &a4, enumSquare::a4, kingMovesets);

    // Center
    U64 d4 = 0ULL;
    std::vector<enumSquare> d4Moves = { d5, e5, e4, e3, d3, c3, c4, c5 };
    setAndCheck(&d4Moves, &board, &d4, enumSquare::d4, kingMovesets);
}
