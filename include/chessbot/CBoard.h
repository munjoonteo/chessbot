#include <string>
#include <unordered_map>

#include "enums.h"
#include "types.h"
#include "pieces/CPiece.h"

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
        int getSquare(enumPiece board, enumSquare square) const;
        void setSquare(enumPiece board, enumSquare square);
        void unsetSquare(enumPiece board, enumSquare square);
        int getCastleState() const;
        void printBB(enumPiece board);
    private:
        const int SIZE = 8;

        void parseFENPieces(std::string fen);

        // Elements correspond to enum enumPiece
        // i.e. pieceBB_[0] is a bitboard representing all White pieces
        U64 pieceBB_[8];

        // Map of squares to pieces (the piece currently on that square)
        std::unordered_map<enumSquare, CPiece> pieceMap_;

        // Current side to move (White or Black)
        enumColour sideToMove_;

        // castling_ ability represented as 4 bits
        // Corresponds to FEN notation KQkq (White king/queenside, Black king/queenside)
        int castling_;

        // Square representing the possible en passant target
        // This can be casted to an enumSquare value (0 - 63)
        int enPassant_;

        // Half-move clock
        // Enforces 50-move rule, reset after captures/pawn moves, incremented otherwise
        int halfmoves_;

        // Full-move counter
        // Incremented after Black's move
        int fullmoves_;

        // TODO
        // Repeated positions count (for stalemates)
};
