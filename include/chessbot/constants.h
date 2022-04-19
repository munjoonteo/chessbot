#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <unordered_map>

#include "enums.h"

namespace Constants {
    const unsigned int QUIET_FLAG = 0;
    const unsigned int DOUBLE_PAWN_PUSH_FLAG = 1;
    const unsigned int KING_CASTLE_FLAG = 2;
    const unsigned int QUEEN_CASTLE_FLAG = 3;
    const unsigned int CAPTURE_FLAG = 4;
    const unsigned int EP_CAPTURE_FLAG = 5;
    const unsigned int N_PROMO_FLAG = 8;
    const unsigned int B_PROMO_FLAG = 9;
    const unsigned int R_PROMO_FLAG = 10;
    const unsigned int Q_PROMO_FLAG = 11;
    const unsigned int N_PROMO_CAPTURE_FLAG = 12;
    const unsigned int B_PROMO_CAPTURE_FLAG = 13;
    const unsigned int R_PROMO_CAPTURE_FLAG = 14;
    const unsigned int Q_PROMO_CAPTURE_FLAG = 15;

    const unsigned int WHITE_KINGSIDE_CASTLE = 8;
    const unsigned int WHITE_QUEENSIDE_CASTLE = 4;
    const unsigned int BLACK_KINGSIDE_CASTLE = 2;
    const unsigned int BLACK_QUEENSIDE_CASTLE = 1;

    const std::unordered_map<char, int> CASTLE_STRING_TO_INT_MAP = {
        {'K', WHITE_KINGSIDE_CASTLE},
        {'Q', WHITE_QUEENSIDE_CASTLE},
        {'k', BLACK_KINGSIDE_CASTLE},
        {'q', BLACK_QUEENSIDE_CASTLE}
    };

    const std::unordered_map<char, enumPiece> PIECE_TO_ENUM_MAP = {
        {'k', enumPiece::nKing},
        {'q', enumPiece::nQueen},
        {'b', enumPiece::nBishop},
        {'n', enumPiece::nKnight},
        {'r', enumPiece::nRook},
        {'p', enumPiece::nPawn}
    };

    const std::unordered_map<std::string, enumSquare> SQUARE_STRING_TO_ENUM_MAP = {
        {"a8", enumSquare::a8},
        {"b8", enumSquare::b8},
        {"c8", enumSquare::c8},
        {"d8", enumSquare::d8},
        {"e8", enumSquare::e8},
        {"f8", enumSquare::f8},
        {"g8", enumSquare::g8},
        {"h8", enumSquare::h8},
        {"a7", enumSquare::a7},
        {"b7", enumSquare::b7},
        {"c7", enumSquare::c7},
        {"d7", enumSquare::d7},
        {"e7", enumSquare::e7},
        {"f7", enumSquare::f7},
        {"g7", enumSquare::g7},
        {"h7", enumSquare::h7},
        {"a6", enumSquare::a6},
        {"b6", enumSquare::b6},
        {"c6", enumSquare::c6},
        {"d6", enumSquare::d6},
        {"e6", enumSquare::e6},
        {"f6", enumSquare::f6},
        {"g6", enumSquare::g6},
        {"h6", enumSquare::h6},
        {"a5", enumSquare::a5},
        {"b5", enumSquare::b5},
        {"c5", enumSquare::c5},
        {"d5", enumSquare::d5},
        {"e5", enumSquare::e5},
        {"f5", enumSquare::f5},
        {"g5", enumSquare::g5},
        {"h5", enumSquare::h5},
        {"a4", enumSquare::a4},
        {"b4", enumSquare::b4},
        {"c4", enumSquare::c4},
        {"d4", enumSquare::d4},
        {"e4", enumSquare::e4},
        {"f4", enumSquare::f4},
        {"g4", enumSquare::g4},
        {"h4", enumSquare::h4},
        {"a3", enumSquare::a3},
        {"b3", enumSquare::b3},
        {"c3", enumSquare::c3},
        {"d3", enumSquare::d3},
        {"e3", enumSquare::e3},
        {"f3", enumSquare::f3},
        {"g3", enumSquare::g3},
        {"h3", enumSquare::h3},
        {"a2", enumSquare::a2},
        {"b2", enumSquare::b2},
        {"c2", enumSquare::c2},
        {"d2", enumSquare::d2},
        {"e2", enumSquare::e2},
        {"f2", enumSquare::f2},
        {"g2", enumSquare::g2},
        {"h2", enumSquare::h2},
        {"a1", enumSquare::a1},
        {"b1", enumSquare::b1},
        {"c1", enumSquare::c1},
        {"d1", enumSquare::d1},
        {"e1", enumSquare::e1},
        {"f1", enumSquare::f1},
        {"g1", enumSquare::g1},
        {"h1", enumSquare::h1},
    };
}

#endif
