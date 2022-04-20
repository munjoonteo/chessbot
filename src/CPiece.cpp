#include "chessbot/constants.h"
#include "chessbot/types.h"
#include "chessbot/CPiece.h"

CPiece::CPiece(enumColour colour, enumSquare startingSquare, char type, Movesets *knight_movesets, Movesets *king_movesets)
    : colour_(colour),
      startingSquare_(startingSquare),
      type_(Constants::PIECE_TO_ENUM_MAP.at(type)),
      knight_movesets_(knight_movesets),
      king_movesets_(king_movesets)
{
    moveset_ = {};
}
