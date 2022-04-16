#include <iostream>

#include <catch2/catch_test_macros.hpp>

#include "chessbot/CBoard.h"
#include "chessbot/constants.h"

void checkBoard(CBoard board, U64 expected[]) {
    for (int i = 0; i < 8; ++i) {
        board.printBB(static_cast<enumPiece>(i));
        CHECK(expected[i] == board.getPieceSet(static_cast<enumPiece>(i)));
    }
}

TEST_CASE("Create board - Initial position") {
    CBoard board = CBoard();

    U64 expected[8] = {
        18446462598732840960,
        65535,
        71776119061282560,
        2594073385365405732,
        4755801206503243842,
        9295429630892703873,
        576460752303423496,
        1152921504606846992,
    };

    checkBoard(board, expected);

    CHECK(board.getCastleState() == (
        Constants::WHITE_KINGSIDE_CASTLE |
        Constants::WHITE_QUEENSIDE_CASTLE |
        Constants::BLACK_KINGSIDE_CASTLE |
        Constants::BLACK_QUEENSIDE_CASTLE
    ));
}

TEST_CASE("Create board - Kiwipete position") {
    CBoard board = CBoard("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -");

    U64 expected[8] = {
        10520166906101497856,
        140746085858705,
        65161534557400320,
        6755399441137664,
        4398317174784,
        9295429630892703873,
        35184372092928,
        1152921504606846992,
    };

    checkBoard(board, expected);

    CHECK(board.getCastleState() == (
        Constants::WHITE_KINGSIDE_CASTLE |
        Constants::WHITE_QUEENSIDE_CASTLE |
        Constants::BLACK_KINGSIDE_CASTLE |
        Constants::BLACK_QUEENSIDE_CASTLE
    ));
}

TEST_CASE("Create board - sparse, no castles") {
    CBoard board = CBoard("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -");

    U64 expected[8] = {
        22518006777118720,
        689342776320,
        22518135609885696,
        0,
        0,
        10737418240,
        0,
        549772591104,
    };

    checkBoard(board, expected);

    CHECK(board.getCastleState() == 0);
}

TEST_CASE("Create board - some castles") {
    CBoard board = CBoard("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");

    U64 expected[8] = {
        7622659127499555072,
        564049488309905,
        57139506205224704,
        12889227264,
        35184399351808,
        2377900603251622017,
        576461851815051264,
        4611686018427387920,
    };

    checkBoard(board, expected);

    CHECK(board.getCastleState() == (
        Constants::BLACK_KINGSIDE_CASTLE |
        Constants::BLACK_QUEENSIDE_CASTLE
    ));
}