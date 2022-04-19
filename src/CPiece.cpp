#include "chessbot/constants.h"
#include "chessbot/CPiece.h"

CPiece::CPiece(enumColour colour, enumSquare startingSquare, char type) : colour_(colour),
    startingSquare_(startingSquare),
    type_(Constants::PIECE_TO_ENUM_MAP.at(type))
{
    // The maximum number of moves any piece can have at one time is 27
    // This occurs with the queen located at any of the four center squares
    // Hence we can preallocate a size of 32 for the piece's moveset
    moveset_ = std::vector<CMove> {};
    moveset_.reserve(32);
}