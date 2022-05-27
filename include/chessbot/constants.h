#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <unordered_map>

#include "enums.h"
#include "types.h"

namespace Constants {
    constexpr unsigned int QUIET_FLAG = 0;
    constexpr unsigned int DOUBLE_PAWN_PUSH_FLAG = 1;
    constexpr unsigned int KING_CASTLE_FLAG = 2;
    constexpr unsigned int QUEEN_CASTLE_FLAG = 3;
    constexpr unsigned int CAPTURE_FLAG = 4;
    constexpr unsigned int EP_CAPTURE_FLAG = 5;
    constexpr unsigned int N_PROMO_FLAG = 8;
    constexpr unsigned int B_PROMO_FLAG = 9;
    constexpr unsigned int R_PROMO_FLAG = 10;
    constexpr unsigned int Q_PROMO_FLAG = 11;
    constexpr unsigned int N_PROMO_CAPTURE_FLAG = 12;
    constexpr unsigned int B_PROMO_CAPTURE_FLAG = 13;
    constexpr unsigned int R_PROMO_CAPTURE_FLAG = 14;
    constexpr unsigned int Q_PROMO_CAPTURE_FLAG = 15;

    constexpr unsigned int WHITE_KINGSIDE_CASTLE = 8;
    constexpr unsigned int WHITE_QUEENSIDE_CASTLE = 4;
    constexpr unsigned int BLACK_KINGSIDE_CASTLE = 2;
    constexpr unsigned int BLACK_QUEENSIDE_CASTLE = 1;

    /* Binary version of mask
        11111111
        10000001
        10000001
        10000001
        10000001
        10000001
        10000001
        11111111
    */
    constexpr U64 EDGE_MASK = 18411139144890810879ULL;

    /* Binary version of mask
        10000001
        00000000
        00000000
        00000000
        00000000
        00000000
        00000000
        10000001
    */
    constexpr U64 CORNER_MASK = 9295429630892703873ULL;

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
        {"a8", enumSquare::a8}, {"b8", enumSquare::b8}, {"c8", enumSquare::c8}, {"d8", enumSquare::d8}, {"e8", enumSquare::e8}, {"f8", enumSquare::f8}, {"g8", enumSquare::g8}, {"h8", enumSquare::h8},
        {"a7", enumSquare::a7}, {"b7", enumSquare::b7}, {"c7", enumSquare::c7}, {"d7", enumSquare::d7}, {"e7", enumSquare::e7}, {"f7", enumSquare::f7}, {"g7", enumSquare::g7}, {"h7", enumSquare::h7},
        {"a6", enumSquare::a6}, {"b6", enumSquare::b6}, {"c6", enumSquare::c6}, {"d6", enumSquare::d6}, {"e6", enumSquare::e6}, {"f6", enumSquare::f6}, {"g6", enumSquare::g6}, {"h6", enumSquare::h6},
        {"a5", enumSquare::a5}, {"b5", enumSquare::b5}, {"c5", enumSquare::c5}, {"d5", enumSquare::d5}, {"e5", enumSquare::e5}, {"f5", enumSquare::f5}, {"g5", enumSquare::g5}, {"h5", enumSquare::h5},
        {"a4", enumSquare::a4}, {"b4", enumSquare::b4}, {"c4", enumSquare::c4}, {"d4", enumSquare::d4}, {"e4", enumSquare::e4}, {"f4", enumSquare::f4}, {"g4", enumSquare::g4}, {"h4", enumSquare::h4},
        {"a3", enumSquare::a3}, {"b3", enumSquare::b3}, {"c3", enumSquare::c3}, {"d3", enumSquare::d3}, {"e3", enumSquare::e3}, {"f3", enumSquare::f3}, {"g3", enumSquare::g3}, {"h3", enumSquare::h3},
        {"a2", enumSquare::a2}, {"b2", enumSquare::b2}, {"c2", enumSquare::c2}, {"d2", enumSquare::d2}, {"e2", enumSquare::e2}, {"f2", enumSquare::f2}, {"g2", enumSquare::g2}, {"h2", enumSquare::h2},
        {"a1", enumSquare::a1}, {"b1", enumSquare::b1}, {"c1", enumSquare::c1}, {"d1", enumSquare::d1}, {"e1", enumSquare::e1}, {"f1", enumSquare::f1}, {"g1", enumSquare::g1}, {"h1", enumSquare::h1},
    };

    const std::unordered_map<enumSquare, std::pair<int, int>> ENUM_TO_COORDS_MAP = {
        {enumSquare::a8, {0, 0}}, {enumSquare::b8, {0, 1}}, {enumSquare::c8, {0, 2}}, {enumSquare::d8, {0, 3}}, {enumSquare::e8, {0, 4}}, {enumSquare::f8, {0, 5}}, {enumSquare::g8, {0, 6}}, {enumSquare::h8, {0, 7}},
        {enumSquare::a7, {1, 0}}, {enumSquare::b7, {1, 1}}, {enumSquare::c7, {1, 2}}, {enumSquare::d7, {1, 3}}, {enumSquare::e7, {1, 4}}, {enumSquare::f7, {1, 5}}, {enumSquare::g7, {1, 6}}, {enumSquare::h7, {1, 7}},
        {enumSquare::a6, {2, 0}}, {enumSquare::b6, {2, 1}}, {enumSquare::c6, {2, 2}}, {enumSquare::d6, {2, 3}}, {enumSquare::e6, {2, 4}}, {enumSquare::f6, {2, 5}}, {enumSquare::g6, {2, 6}}, {enumSquare::h6, {2, 7}},
        {enumSquare::a5, {3, 0}}, {enumSquare::b5, {3, 1}}, {enumSquare::c5, {3, 2}}, {enumSquare::d5, {3, 3}}, {enumSquare::e5, {3, 4}}, {enumSquare::f5, {3, 5}}, {enumSquare::g5, {3, 6}}, {enumSquare::h5, {3, 7}},
        {enumSquare::a4, {4, 0}}, {enumSquare::b4, {4, 1}}, {enumSquare::c4, {4, 2}}, {enumSquare::d4, {4, 3}}, {enumSquare::e4, {4, 4}}, {enumSquare::f4, {4, 5}}, {enumSquare::g4, {4, 6}}, {enumSquare::h4, {4, 7}},
        {enumSquare::a3, {5, 0}}, {enumSquare::b3, {5, 1}}, {enumSquare::c3, {5, 2}}, {enumSquare::d3, {5, 3}}, {enumSquare::e3, {5, 4}}, {enumSquare::f3, {5, 5}}, {enumSquare::g3, {5, 6}}, {enumSquare::h3, {5, 7}},
        {enumSquare::a2, {6, 0}}, {enumSquare::b2, {6, 1}}, {enumSquare::c2, {6, 2}}, {enumSquare::d2, {6, 3}}, {enumSquare::e2, {6, 4}}, {enumSquare::f2, {6, 5}}, {enumSquare::g2, {6, 6}}, {enumSquare::h2, {6, 7}},
        {enumSquare::a1, {7, 0}}, {enumSquare::b1, {7, 1}}, {enumSquare::c1, {7, 2}}, {enumSquare::d1, {7, 3}}, {enumSquare::e1, {7, 4}}, {enumSquare::f1, {7, 5}}, {enumSquare::g1, {7, 6}}, {enumSquare::h1, {7, 7}},
    };

    // square & rankN == 1 means that square is in the corresponding rank
    constexpr U64 RANK_1 = 0x00000000000000FFULL;
    constexpr U64 RANK_4 = 0x00000000FF000000ULL;
    constexpr U64 RANK_5 = 0x000000FF00000000ULL;
    constexpr U64 RANK_8 = 0xFF00000000000000ULL;

    constexpr U64 FILE_1 = 0x8080808080808080ULL;
    constexpr U64 FILE_8 = 0x0101010101010101ULL;

    const std::vector<std::pair<int, int>> BISHOP_RAYS = { { { 1, 1 }, { 1, -1 }, { -1, -1 }, { -1, 1 } } };
    const std::vector<std::pair<int, int>> ROOK_RAYS = { { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } } };
}

#endif
