#include <iostream>

#include <catch2/catch_test_macros.hpp>

#include "chessbot/CBoard.h"

TEST_CASE("Create board") {
    CBoard a = CBoard();

    U64 expected[8] = {
        18446462598732840960,
        65535,
        71776119061282560,
        2594073385365405732,
        4755801206503243842,
        9295429630892703873,
        576460752303423504,
        1152921504606846984,
    };

    for (int i = 0; i < 8; ++i) {
        CHECK(expected[i] == a.getPieceSet(static_cast<enumPiece>(i)));
    }
}