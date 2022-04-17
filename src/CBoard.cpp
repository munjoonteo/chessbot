#include <iostream>
#include <sstream>

#include "chessbot/CBoard.h"
#include "chessbot/constants.h"

CBoard::CBoard()
    try : CBoard::CBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1") {
    } catch (std::invalid_argument& e) {
        throw e;
    }

CBoard::CBoard(std::string fen)  {
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

    halfmoves = 0;
    fullmoves = 1;

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

                sideToMove = (field == "w") ? enumColour::white : enumColour::black;

                break;
            case 2:
                // Castling availability
                if (field.size() < 1 or field.size() > 4) throw std::invalid_argument("Invalid FEN string");

                castling = 0;

                for (std::size_t i = 0; i < field.size(); ++i) {
                    if (Constants::CASTLE_STRING_TO_INT_MAP.contains(field[i])) {
                        castling |= Constants::CASTLE_STRING_TO_INT_MAP.at(field[i]);
                    } else if (field[i] == '-') {
                        continue;
                    } else {
                        throw std::invalid_argument("Invalid FEN string");
                    }
                }

                break;
            case 3:
                // En Passant
                if (field == "-") {
                    enPassant = -1;
                } else {
                    try {
                        enPassant = Constants::SQUARE_STRING_TO_ENUM_MAP.at(field);
                    } catch (std::out_of_range& e) {
                        throw std::invalid_argument("Invalid FEN string");
                    }
                }

                break;
            case 4:
                // Halfmove count
                try {
                    halfmoves = std::stoi(field);
                } catch (std::invalid_argument& e) {
                    throw std::invalid_argument("Invalid FEN string");
                } catch (std::out_of_range& e) {
                    throw std::invalid_argument("Invalid FEN string");
                }

                break;
            case 5:
                // Fullmove count
                try {
                    fullmoves = std::stoi(field);
                } catch (std::invalid_argument& e) {
                    throw std::invalid_argument("Invalid FEN string");
                } catch (std::out_of_range& e) {
                    throw std::invalid_argument("Invalid FEN string");
                }

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

        for (auto c : rank) {
            int cNum = c - '0';
            if (cNum <= 0) {
                throw std::invalid_argument("Invalid FEN string");
            } else if (cNum >= 1 and cNum <= 9) {
                currFile += cNum;
            } else {
                auto currSquare = static_cast<enumSquare>(currRank * SIZE + currFile);

                try {
                    CBoard::setSquare(Constants::PIECE_TO_ENUM_MAP.at(tolower(c)), currSquare);
                } catch (std::out_of_range& e) {
                    throw std::invalid_argument("Invalid FEN string");
                } catch(std::invalid_argument& e) {
                    throw e;
                }

                if (c >= 'A' and c <= 'Z') {
                    CBoard::setSquare(enumPiece::nWhite, currSquare);
                } else if (c >= 'a' and c <= 'z') {
                    CBoard::setSquare(enumPiece::nBlack, currSquare);
                }

                ++currFile;
            }
        }

        if (currFile != SIZE) throw std::invalid_argument("Invalid FEN string");

        ++currRank;
    }

    if (currRank != SIZE) throw std::invalid_argument("Invalid FEN string");
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
int CBoard::getSquare(enumPiece board, enumSquare square) {
    if (square < 0 or square > 63) throw  std::invalid_argument("Invalid square");

    return (pieceBB[board] & (1ULL << square)) ? 1 : 0;
}

// Sets the given square on the given bitboard to 1, meaning it is occupied
void CBoard::setSquare(enumPiece board, enumSquare square) {
    if (square < 0 or square > 63) throw  std::invalid_argument("Invalid square");

    pieceBB[board] |= (1ULL << square);
}

// Sets the given square on the given bitboard to 0, meaning it is unoccupied
void CBoard::unsetSquare(enumPiece board, enumSquare square) {
    if (square < 0 or square > 63) throw  std::invalid_argument("Invalid square");

    if (CBoard::getSquare(board, square)) pieceBB[board] ^= (1ULL << square);
}

int CBoard::getCastleState() {
    return castling;
}

void CBoard::printBB(enumPiece board) {
    U64 target = pieceBB[board];

    for (int rank = 0; rank < SIZE; ++rank) {
        // Print ranks on left
        std::cout << SIZE - rank << "  ";

        for (int file = 0; file < SIZE; ++file) {
            // Get the index of the bit corresponding to the current rank and file
            auto currSquare = static_cast<enumSquare>(rank * SIZE + file);
            std::cout << " " << getSquare(board, currSquare);
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