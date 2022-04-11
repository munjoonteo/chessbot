#include <iostream>
#include "chessbot/CBoard.h"

CBoard::CBoard() : CBoard::CBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1") {}

CBoard::CBoard(std::string fen)  {
    // TODO initialise with FEN notation

    sideToMove = enumColour::white;
    castling = 15; // 1111 in binary is 15 in decimal
    enPassant = -1;
    halfmoves = 0;
    fullmoves = 0;
}

void CBoard::changeTurn() {
    if (sideToMove == enumColour::white) {
        sideToMove = enumColour::black;
    } else {
        sideToMove = enumColour::white;
        ++fullmoves;
    }

    ++halfmoves;
}

U64 CBoard::getPieceSet(enumPiece piece) const {
    return pieceBB[piece];
}

U64 CBoard::getPieceSet(enumPiece piece, enumPiece colour) const {
    return pieceBB[piece] && pieceBB[colour];
}

// Returns 1 if there is a piece on the given square on the given bitboard
// Returns 0 otherwise
int CBoard::getSquare(enumPiece board, int square) {
    return (pieceBB[board] & (1ULL << square)) ? 1 : 0;
}

// Sets the given square on the given bitboard to 1, meaning it is occupied
void CBoard::setSquare(enumPiece board, enumSquare square) {
    pieceBB[board] |= (1ULL << square);
}

// Sets the given square on the given bitboard to 0, meaning it is unoccupied
void CBoard::unsetSquare(enumPiece board, enumSquare square) {
    if (CBoard::getSquare(board, square)) pieceBB[board] ^= (1ULL << square);
}

void CBoard::printBB(enumPiece board) {
    U64 target = pieceBB[board];

    for (int rank = 0; rank < SIZE; ++rank) {
        // Print ranks on left
        std::cout << SIZE - rank << "  ";

        for (int file = 0; file < SIZE; ++file) {
            // Get the index of the bit corresponding to the current rank and file
            std::cout << " " << getSquare(board, rank * SIZE + file);
        }

        std::cout << "\n";
    }

    // Print files on bottom
    std::cout << "\n    ";
    for (int file = 0; file < SIZE; ++file) {
        std::cout << static_cast<char>('a' + file) << " ";
    }

    // Print numerical representation of bitboard
    std::cout << "\n" << "Bitboard: " << target << "\n";
}