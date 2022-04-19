#include "chessbot/constants.h"
#include "chessbot/pieces/CPiece.h"

CPiece::CPiece(enumColour colour, enumSquare startingSquare, char type) : colour_(colour),
    startingSquare_(startingSquare),
    type_(Constants::PIECE_TO_ENUM_MAP.at(type))
{}