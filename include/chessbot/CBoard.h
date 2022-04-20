#include <array>
#include <string>
#include <unordered_map>

#include "enums.h"
#include "types.h"

class CBoard {
    public:
        // Constructors
        CBoard();
        CBoard(std::string fen);

        // Game related functions
        void changeTurn();

        // Utility functions
        U64 getOccupiedSquares() const;
        U64 getEmptySquares() const;

        U64 getPieceSet(enumPiece piece) const;
        U64 getPieceSet(enumPiece piece, enumPiece colour) const;

        int getSquare(enumPiece board, enumSquare square) const;
        void setSquare(enumPiece board, enumSquare square);
        U64 setSquare(U64 board, int square);
        void unsetSquare(enumPiece board, enumSquare square);

        int getCastleState() const;

        void printBB(enumPiece board);
    private:
        void parseFENPieces(std::string fen);

        U64 shiftNorthOne(U64 bitboard);
        U64 shiftSouthOne(U64 bitboard);

        U64 wPawnPushTargets();
        U64 bPawnPushTargets();
        U64 wPawnDoublePushTargets();
        U64 bPawnDoublePushTargets();
        U64 wPawnsCanPush();
        U64 bPawnsCanPush();
        U64 wPawnsCanDoublePush();
        U64 bPawnsCanDoublePush();
        void generateKnightMovesets();
        void generateKingMovesets();

        // 1 means that square is in the corresponding rank
        const U64 rank4 = 0x00000000FF000000ULL;
        const U64 rank5 = 0x000000FF00000000ULL;

        // Elements correspond to enum enumPiece
        // i.e. pieceBB_[0] is a bitboard representing all White pieces
        std::array<U64, 8> pieceBB_;

        // Current side to move (White or Black)
        enumColour sideToMove_;

        // castling_ ability represented as 4 bits
        // Corresponds to FEN notation KQkq (White king/queenside, Black king/queenside)
        int castling_;

        // Square representing the possible en passant target
        // This can be casted to an enumSquare value (0 - 63)
        enumSquare enPassant_;

        // Half-move clock
        // Enforces 50-move rule, reset after captures/pawn moves, incremented otherwise
        int halfmoves_;

        // Full-move counter
        // Incremented after Black's move
        int fullmoves_;

        // TODO
        // Repeated positions count (for stalemates)

        // Precomputed non-sliding piece movesets
        // Pawns can be calculated because dealing with different colours is hard
        Movesets knight_movesets_;
        Movesets king_movesets_;
};
