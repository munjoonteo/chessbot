#include <string>

#include "chessbot/enums.h"
#include "chessbot/types.h"

class CBoard {
    public:
        // Constructors
        CBoard();
        CBoard(std::string fen);

        // Game related functions
        void changeTurn();

        // Utility functions
        U64 getPieceSet(enumPiece piece) const;
        U64 getPieceSet(enumPiece piece, enumPiece colour) const;
        int getSquare(enumPiece board, int square);
        void setSquare(enumPiece board, enumSquares square);
        void unsetSquare(enumPiece board, enumSquares square);
        void printBB(enumPiece board);
    private:
        const int SIZE = 8;

        // Elements correspond to enum enumPiece
        // i.e. pieceBB[0] is a bitboard representing all white pieces
        U64 pieceBB[8];

        // Current side to move (white or black)
        enumColour sideToMove;

        // Castling ability represented as 4 bits
        // Corresponds to FEN notation KQkq (white king/queenside, black king/queenside)
        int castling;

        // Square representing the possible en passant target
        U64 enPassant;

        // Half-move clock
        // Enforces 50-move rule, reset after captures/pawn moves, incremented otherwise
        int halfmoves;

        // Full-move counter
        // Incremented after Black's move
        int fullmoves;
};