#include <iostream>
#include <sstream>

#include "chessbot/CBoard.h"
#include "chessbot/constants.h"
#include "chessbot/magics_64.h"

CBoard::CBoard()
    try : CBoard::CBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1") {
    } catch (std::invalid_argument& e) {
        throw e;
    }

CBoard::CBoard(std::string fen) {
    // Precompute non-sliding piece movesets
    CBoard::generateKingMovesets();
    CBoard::generateKnightMovesets();

    CBoard::generateBlockerMasks(enumPiece::nBishop);
    CBoard::generateBlockerMasks(enumPiece::nRook);

    CBoard::generateSlidingMovesets(enumPiece::nBishop);
    CBoard::generateSlidingMovesets(enumPiece::nRook);

    CBoard::parseFen(fen);
}

void CBoard::parseFen(std::string fen) {
    // FEN Notation explained:
    // Fields are separated by spaces

    // Field 1: Piece arrangement
    // Upper case letters represent White's pieces
    // Lower case letters represent Black's pieces
    // A slash denotes the end of a rank. Ranks start from 8 down to 1.
    // A number denotes a certain number of consecutive empty squares

    // Field 2: Side to move (w or b)
    // Field 3: Castling availability (White king/queenside, Black king/queenside)
    // Field 4: En Passant target square in algebraic notation
    // Field 5: Halfmove clock
    // Field 6: Fullmove clock

    std::stringstream ss(fen);
    std::string field;
    int currField = 0;

    for (int i = 0; i < 8; ++i) pieceBB_[i] = 0ULL;

    castling_ = 0;
    enPassant_ = enumSquare::no_sq;
    halfmoves_ = 0;
    fullmoves_ = 1;

    while (ss >> field) {
        switch(currField) {
            case 0:
                // Piece arrangement
                try {
                    CBoard::parseFENPieces(field);
                } catch(std::invalid_argument& e) {
                    throw e;
                }

                break;
            case 1:
                // Side to move
                if (field != "w" and field != "b") throw std::invalid_argument("Invalid FEN string");

                sideToMove_ = (field == "w") ? enumColour::white : enumColour::black;

                break;
            case 2:
                // castling_ availability
                if (field.size() < 1 or field.size() > 4) throw std::invalid_argument("Invalid FEN string");

                castling_ = 0;

                for (std::size_t i = 0; i < field.size(); ++i) {
                    if (Constants::CASTLE_STRING_TO_INT_MAP.contains(field[i])) {
                        castling_ |= Constants::CASTLE_STRING_TO_INT_MAP.at(field[i]);
                    } else if (field[i] == '-') {
                        continue;
                    } else {
                        throw std::invalid_argument("Invalid FEN string");
                    }
                }

                break;
            case 3:
                // En Passant
                if (field != "-") {
                    try {
                        enPassant_ = Constants::SQUARE_STRING_TO_ENUM_MAP.at(field);
                    } catch (std::out_of_range& e) {
                        throw std::invalid_argument("Invalid FEN string");
                    }
                }

                break;
            case 4:
                // Halfmove count
                try {
                    halfmoves_ = std::stoi(field);
                } catch (std::invalid_argument& e) {
                    throw std::invalid_argument("Invalid FEN string");
                } catch (std::out_of_range& e) {
                    throw std::invalid_argument("Invalid FEN string");
                }

                if (halfmoves_ < 0) throw std::invalid_argument("Invalid FEN string");

                break;
            case 5:
                // Fullmove count
                try {
                    fullmoves_ = std::stoi(field);
                } catch (std::invalid_argument& e) {
                    throw std::invalid_argument("Invalid FEN string");
                } catch (std::out_of_range& e) {
                    throw std::invalid_argument("Invalid FEN string");
                }

                if (fullmoves_ < 0) throw std::invalid_argument("Invalid FEN string");

                break;
        }

        ++currField;
    }

}

void CBoard::parseFENPieces(std::string fen) {
    std::stringstream ss(fen);
    std::string rank;

    int currRank = 0;

    while (getline(ss, rank, '/')) {
        int currFile = 0;

        for (auto fenChar : rank) {
            if (std::isdigit(fenChar)) {
                currFile += fenChar - '0';
            } else if (std::isalpha(fenChar)) {
                auto currSquare = getSquareFromCoords(currRank, currFile);
                char fenCharLower = tolower(fenChar);

                try {
                    CBoard::setSquare(Constants::PIECE_TO_ENUM_MAP.at(fenCharLower), currSquare);
                } catch (std::out_of_range& e) {
                    throw std::invalid_argument("Invalid FEN string");
                } catch(std::invalid_argument& e) {
                    throw e;
                }

                if (fenChar >= 'A' and fenChar <= 'Z') {
                    CBoard::setSquare(enumPiece::nWhite, currSquare);
                } else if (fenChar >= 'a' and fenChar <= 'z') {
                    CBoard::setSquare(enumPiece::nBlack, currSquare);
                }

                ++currFile;
            } else {
                throw std::invalid_argument("Invalid FEN string");
            }
        }

        if (currFile != 8) throw std::invalid_argument("Invalid FEN string");

        ++currRank;
    }

    if (currRank != 8) throw std::invalid_argument("Invalid FEN string");
}

enumSquare CBoard::getSquareFromCoords(int rank, int file) {
    return static_cast<enumSquare>(rank * 8 + file);
}

void CBoard::changeTurn() {
    if (sideToMove_ == enumColour::white) {
        sideToMove_ = enumColour::black;
    } else {
        sideToMove_ = enumColour::white;
        ++fullmoves_;
    }

    ++halfmoves_;
}

U64 CBoard::getOccupiedSquares() const {
    return pieceBB_[enumPiece::nWhite] | pieceBB_[enumPiece::nBlack];
}

U64 CBoard::getEmptySquares() const {
    return ~CBoard::getOccupiedSquares();
}

U64 CBoard::getPieceSet(enumPiece piece) const {
    return pieceBB_[piece];
}

U64 CBoard::getPieceSet(enumPiece piece, enumPiece colour) const {
    return pieceBB_[piece] & pieceBB_[colour];
}

// Returns 1 if there is a piece on the given square on the given bitboard
// Returns 0 otherwise
bool CBoard::getSquare(U64 board, enumSquare square) const {
    if (square < 0 or square > 63) throw  std::invalid_argument("Invalid square");

    return (board & (1ULL << square)) ? 1 : 0;
}

bool CBoard::getSquare(enumPiece board, enumSquare square) const {
    return CBoard::getSquare(pieceBB_[board], square);
}

// Sets the given square on the given bitboard to 1, meaning it is occupied
void CBoard::setSquare(U64 *board, enumSquare square) const {
    if (square < 0 or square > 63) throw  std::invalid_argument("Invalid square");

    *board |= (1ULL << square);
}

void CBoard::setSquare(enumPiece board, enumSquare square) {
    if (square < 0 or square > 63) throw  std::invalid_argument("Invalid square");

    pieceBB_[board] |= (1ULL << square);
}

// Sets the given square on the given bitboard to 0, meaning it is unoccupied
void CBoard::unsetSquare(U64 *board, enumSquare square) const {
    if (square < 0 or square > 63) throw  std::invalid_argument("Invalid square");

    if (CBoard::getSquare(*board, square)) *board ^= (1ULL << square);
}

void CBoard::unsetSquare(enumPiece board, enumSquare square) {
    if (square < 0 or square > 63) throw  std::invalid_argument("Invalid square");

    if (CBoard::getSquare(board, square)) pieceBB_[board] ^= (1ULL << square);
}

int CBoard::getCastleState() const {
    return castling_;
}

const Movesets *CBoard::getKnightMovesets() const {
    return &knightMovesets_;
}

const Movesets *CBoard::getKingMovesets() const {
    return &kingMovesets_;
}

const U64 CBoard::getKnightMoveset(enumSquare square, U64 friendlyPieces) {
    return knightMovesets_[square] & ~friendlyPieces;
}

const U64 CBoard::getKingMoveset(enumSquare square, U64 friendlyPieces) {
    return kingMovesets_[square] & ~friendlyPieces;
}

const Movesets *CBoard::getBishopBlockerMasks() const {
    return &bishopBlockerMasks_;
}

const Movesets *CBoard::getRookBlockerMasks() const {
    return &rookBlockerMasks_;
}

const U64 CBoard::getBishopMoveset(enumSquare square, U64 blockers, U64 friendlyPieces) {
    blockers &= bishopBlockerMasks_[square];

    U64 key = (blockers * bishopMagics[square]) >> (64 - bishopBits[square]);

    return bishopMovesets_[square][key];
}

const U64 CBoard::getRookMoveset(enumSquare square, U64 blockers, U64 friendlyPieces) {
    blockers &= rookBlockerMasks_[square];

    U64 key = (blockers * rookMagics[square]) >> (64 - rookBits[square]);

    return rookMovesets_[square][key];
}

const U64 CBoard::getQueenMoveset(enumSquare square, U64 blockers, U64 friendlyPieces) {
    return CBoard::getBishopMoveset(square, blockers, friendlyPieces) |
           CBoard::getRookMoveset(square, blockers, friendlyPieces);
}

void CBoard::printBB(U64 board) {
    for (int rank = 0; rank < 8; ++rank) {
        // Print ranks on left
        std::cout << 8 - rank << "  ";

        for (int file = 0; file < 8; ++file) {
            std::cout << " " << getSquare(board, CBoard::getSquareFromCoords(rank, file));
        }

        std::cout << "\n";
    }

    // Print files on bottom
    std::cout << "\n    ";
    for (int file = 0; file < 8; ++file) {
        std::cout << static_cast<char>('a' + file) << " ";
    }

    // Print numerical representation of bitboard
    std::cout << "\n" << "Bitboard: " << board << "\n";
}

void CBoard::printBB(enumPiece board) {
    CBoard::printBB(pieceBB_[board]);
}

U64 CBoard::shiftNorthOne(U64 bitboard) {
    return bitboard << 8;
}

U64 CBoard::shiftSouthOne(U64 bitboard) {
    return bitboard >> 8;
}

U64 CBoard::wPawnPushTargets() {
    return
        CBoard::shiftNorthOne(CBoard::getPieceSet(enumPiece::nPawn, enumPiece::nWhite))
        & CBoard::getEmptySquares();
}

U64 CBoard::bPawnPushTargets() {
    return
        CBoard::shiftSouthOne(CBoard::getPieceSet(enumPiece::nPawn, enumPiece::nBlack))
        & CBoard::getEmptySquares();
}

U64 CBoard::wPawnDoublePushTargets() {
    U64 singlePush = CBoard::wPawnPushTargets();
    return CBoard::shiftNorthOne(singlePush) & CBoard::getEmptySquares() & Constants::RANK_4;
}

U64 CBoard::bPawnDoublePushTargets() {
    U64 singlePush = CBoard::bPawnPushTargets();
    return CBoard::shiftSouthOne(singlePush) & CBoard::getEmptySquares() & Constants::RANK_5;
}

U64 CBoard::wPawnsCanPush() {
    return CBoard::shiftSouthOne(CBoard::getEmptySquares()) & CBoard::getPieceSet(enumPiece::nPawn, enumPiece::nWhite);
}

U64 CBoard::bPawnsCanPush() {
    return CBoard::shiftNorthOne(CBoard::getEmptySquares()) & CBoard::getPieceSet(enumPiece::nPawn, enumPiece::nBlack);
}

U64 CBoard::wPawnsCanDoublePush() {
    U64 emptySquares = CBoard::getEmptySquares();
    U64 emptyRank3 = CBoard::shiftSouthOne(emptySquares & Constants::RANK_4) & emptySquares;
    return CBoard::getPieceSet(enumPiece::nPawn, enumPiece::nWhite) & CBoard::shiftSouthOne(emptyRank3);
}

U64 CBoard::bPawnsCanDoublePush() {
    U64 emptySquares = CBoard::getEmptySquares();
    U64 emptyRank6 = CBoard::shiftNorthOne(emptySquares & Constants::RANK_5) & emptySquares;
    return CBoard::getPieceSet(enumPiece::nPawn, enumPiece::nBlack) & CBoard::shiftNorthOne(emptyRank6);
}

void CBoard::generateNonSlidingMovesets(const int* deltaRank, const int* deltaFile, Movesets *moveset) {
    for (int i = 0; i < 64; ++i) {
        U64 bitboard = 0ULL;
        std::pair<int, int> coords = Constants::ENUM_TO_COORDS_MAP.at(static_cast<enumSquare>(i));
        int currRank = coords.first;
        int currFile = coords.second;

        for (int j = 0; j < 8; ++j) {
            int newRank = currRank + deltaRank[j];
            int newFile = currFile + deltaFile[j];

            if (!CBoard::isLegalSquare(newRank, newFile)) continue;

            CBoard::setSquare(&bitboard, CBoard::getSquareFromCoords(newRank, newFile));
        }

        moveset->at(i) = bitboard;
    }
}

void CBoard::generateKnightMovesets() {
    // Starting from south-south-east move
    const int deltaRank[] = { -2, -1, 1, 2, 2, 1, -1, -2 };
    const int deltaFile[] = { 1, 2, 2, 1, -1, -2, -2, -1 };
    CBoard::generateNonSlidingMovesets(deltaRank, deltaFile, &knightMovesets_);
}

void CBoard::generateKingMovesets() {
    // Starting from vertical move
    const int deltaRank[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
    const int deltaFile[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
    CBoard::generateNonSlidingMovesets(deltaRank, deltaFile, &kingMovesets_);
}

void CBoard::generateBlockerMasks(enumPiece piece) {
    std::vector<std::pair<int, int>> possibleRays;
    Movesets *blockerMasks;
    std::array<BlockerVector, 64> *blockerVectors;

    if (piece == enumPiece::nBishop) {
        possibleRays = Constants::BISHOP_RAYS;
        blockerMasks = &bishopBlockerMasks_;
        blockerVectors = &bishopBlockerVectors_;
    } else if (piece == enumPiece::nRook) {
        possibleRays = Constants::ROOK_RAYS;
        blockerMasks = &rookBlockerMasks_;
        blockerVectors = &rookBlockerVectors_;
    } else {
        throw std::invalid_argument("Invalid piece");
    }

    for (auto curr : Constants::ENUM_TO_COORDS_MAP) {
        U64 bb = 0ULL;

        enumSquare currSquare = curr.first;
        int currRank = curr.second.first;
        int currFile = curr.second.second;

        for (auto ray: possibleRays) {
            int blockerRank = currRank + ray.first;
            int blockerFile = currFile + ray.second;

            while (CBoard::isLegalSquare(blockerRank, blockerFile)) {
                enumSquare currBlocker = getSquareFromCoords(blockerRank, blockerFile);
                CBoard::setSquare(&bb, currBlocker);

                blockerRank += ray.first;
                blockerFile += ray.second;
            }
        }


        U64 noEdges = CBoard::clearEdges(bb, currSquare);
        blockerMasks->at(currSquare) = noEdges;

        // Generate blockers after edges have been cleared
        BlockerVector blockers = {};

        for (int rank = 0; rank < 8; ++rank) {
            for (int file = 0; file < 8; ++file) {
                enumSquare currBlocker = CBoard::getSquareFromCoords(rank, file);
                if (CBoard::getSquare(noEdges, currBlocker)) {
                    blockers.emplace_back(currBlocker);
                }
            }
        }
        blockerVectors->at(currSquare) = blockers;
    }
}

U64 CBoard::clearEdges(U64 bb, enumSquare square) {
    // Remove edge squares from bitboard to create blocker mask
    // If the current square is on an edge, only remove the corners and the edge on the other direction

    if (CBoard::isEdge(square)) {
        bb &= ~Constants::CORNER_MASK;

        if (CBoard::isCorner(square)) return bb;

        if (square < 8) {
            return bb & ~Constants::RANK_8;
        } else if (square >= 56) {
            return bb & ~Constants::RANK_1;
        } else if (square % 8 == 0) {
            return bb & ~Constants::FILE_8;
        } else {
            return bb & ~Constants::FILE_1;
        }
    } else {
        return bb & ~Constants::EDGE_MASK;
    }
}

bool CBoard::isLegalSquare(int rank, int file) {
    return (rank >= 0 and rank < 8 and file >= 0 and file < 8);
}

bool CBoard::isEdge(enumSquare square) {
    U64 bb = 0ULL;
    CBoard::setSquare(&bb, square);

    return Constants::EDGE_MASK & bb;
}

bool CBoard::isCorner(enumSquare square) {
    U64 bb = 0ULL;
    CBoard::setSquare(&bb, square);

    return Constants::CORNER_MASK & bb;
}

bool CBoard::isOrthogonallyAdjacent(enumSquare s1, enumSquare s2) {
    if (s1 == enumSquare::no_sq or s2 == enumSquare::no_sq) return false;

    auto [s1_x, s1_y] = Constants::ENUM_TO_COORDS_MAP.at(s1);
    auto [s2_x, s2_y] = Constants::ENUM_TO_COORDS_MAP.at(s2);

    // XOR here to not include diagonals
    return (std::abs(s1_x - s2_x) == 1) ^ (std::abs(s1_y - s2_y) == 1);
}

void CBoard::generateSlidingMovesets(enumPiece piece) {
    std::array<BlockerVector, 64> *blockerVectors;
    std::array<std::unordered_map<U64, U64>, 64> *movesets;
    const U64 *magics;
    const int *bits;

    if (piece == enumPiece::nBishop) {
        blockerVectors = &bishopBlockerVectors_;
        movesets = &bishopMovesets_;
        magics = bishopMagics;
        bits = bishopBits;
    } else if (piece == enumPiece::nRook) {
        blockerVectors = &rookBlockerVectors_;
        movesets = &rookMovesets_;
        magics = rookMagics;
        bits = rookBits;
    } else {
        throw std::invalid_argument("Invalid piece");
    }

    for (int i = 0; i < 64; ++i) {
        auto blockerVector = blockerVectors->at(i);
        std::vector<BlockerVector> combinations = {};

        // Generate all combinations of bits[i] possible blockers for each square
        // i.e. 1 blocker, 2 blockers up to bits[i] blockers
        for (int j = 1; j <= bits[i]; ++j) {
            getCombination(&combinations, &blockerVector, j);

            // Convert blockers back into a bitboard
            // Generate key with the corresponding magic number
            // Fill in appropriate slot in corresponding moveset
            for (auto combination : combinations) {
                U64 blockerBB = 0ULL;
                for (auto blocker : combination) CBoard::setSquare(&blockerBB, blocker);

                U64 movesetBB = CBoard::getMovesetFromBlockers(
                    static_cast<enumSquare>(i),
                    piece,
                    blockerBB
                );

                U64 key = (blockerBB * magics[i]) >> (64 - bits[i]);

                movesets->at(i)[key] = movesetBB;
            }
        }
    }
}

void CBoard::getCombination(std::vector<BlockerVector> *combinations, BlockerVector *blockers, int nBlockers) {
    BlockerVector currCombination(nBlockers);

    CBoard::getCombinationRecurse(combinations, blockers, &currCombination, 0, blockers->size() - 1, 0, nBlockers);
}

void CBoard::getCombinationRecurse(
    std::vector<BlockerVector> *combinations,
    BlockerVector *blockers,
    BlockerVector *currCombination,
    int start, int end, int currCombIdx, int nBlockers
) {
    if (currCombIdx == nBlockers) {
        combinations->emplace_back(*currCombination);
        return;
    }

    for (int i = start; i <= end && end - i + 1 >= nBlockers - currCombIdx; ++i) {
        currCombination->at(currCombIdx) = blockers->at(i);
        CBoard::getCombinationRecurse(combinations, blockers, currCombination, i + 1, end, currCombIdx + 1, nBlockers);
    }
}

U64 CBoard::getMovesetFromBlockers(enumSquare square, enumPiece piece, U64 blockerBB) {
    U64 moveset = 0ULL;

    auto possibleRays = piece == enumPiece::nBishop ? Constants::BISHOP_RAYS : Constants::ROOK_RAYS;

    auto coords = Constants::ENUM_TO_COORDS_MAP.at(square);
    int startRank = coords.first;
    int startFile = coords.second;

    for (auto ray : possibleRays) {
        int currRank = startRank + ray.first;
        int currFile = startFile + ray.second;

        while (CBoard::isLegalSquare(currRank, currFile)) {
            enumSquare currSquare = CBoard::getSquareFromCoords(currRank, currFile);
            CBoard::setSquare(&moveset, currSquare);

            if (CBoard::getSquare(blockerBB, currSquare) == 1) break;

            currRank += ray.first;
            currFile += ray.second;
        }
    }

    return moveset;
}
