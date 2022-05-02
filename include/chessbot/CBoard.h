#include <array>
#include <string>
#include <unordered_map>
#include <vector>

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

        bool getSquare(U64 board, enumSquare square) const;
        bool getSquare(enumPiece board, enumSquare square) const;

        void setSquare(U64 *board, enumSquare square) const;
        void setSquare(enumPiece board, enumSquare square);

        void unsetSquare(enumPiece board, enumSquare square);

        // Getters
        int getCastleState() const;

        const Movesets *getKnightMovesets() const;
        const Movesets *getKingMovesets() const;
        const U64 getKnightMoveset(enumSquare square, U64 friendlyPieces);
        const U64 getKingMoveset(enumSquare square, U64 friendlyPieces);

        const Movesets *getBishopBlockerMasks() const;
        const Movesets *getRookBlockerMasks() const;
        const U64 getBishopMoveset(enumSquare square, U64 blockers, U64 friendlyPieces);
        const U64 getRookMoveset(enumSquare square, U64 blockers, U64 friendlyPieces);
        const U64 getQueenMoveset(enumSquare square, U64 blockers, U64 friendlyPieces);

        // Printing bitboards
        void printBB(U64 board);
        void printBB(enumPiece board);
    private:
        void parseFen(std::string fen);
        void parseFENPieces(std::string fen);

        enumSquare getSquareFromCoords(int rank, int file);

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

        void generateNonSlidingMovesets(const int *deltaRank, const int *deltaFile, Movesets *moveset);
        void generateKnightMovesets();
        void generateKingMovesets();

        // Masks generated using the classical rays technique
        void generateBlockerMasks(enumPiece piece);
        bool isLegalSquare(int rank, int file);
        bool isEdge(int rank, int file);
        bool isCorner(int rank, int file);

        void generateSlidingMovesets();
        void generateBishopMovesets();
        void generateRookMovesets();

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
        Movesets knightMovesets_;
        Movesets kingMovesets_;

        // Precomputed sliding piece moveset generators
        // https://stackoverflow.com/questions/16925204/sliding-move-generation-using-magic-bitboard

        // Bitboards representing all possible squares which have pieces
        // which can block the movement of a bishop/rook on a particular square

        // Note: The edges do not have to be included because the piece is able to
        // move to an edge square regardless of whether there is a piece there or not
        Movesets bishopBlockerMasks_;
        Movesets rookBlockerMasks_;

        // Blockers in vector of squares form, to simplify generation of all possble blockers.
        std::array<std::vector<enumSquare>, 64> bishopBlockerVectors_;
        std::array<std::vector<enumSquare>, 64> rookBlockerVectors_;

        // Bitboards representing the attack set of a bishop/rook given a particular square and
        // an index derived from hashing the current blocking pieces via the magic numbers in magics_64.h
        std::array<std::array<U64, 64>, 64> bishopMovesets_;
        std::array<std::array<U64, 64>, 64> rookMovesets_;
};
