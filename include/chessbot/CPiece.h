#include "enums.h"
#include "CMove.h"

class CPiece {
    public:
        CPiece(enumColour colour = enumColour::white,
              enumSquare startingSquare = enumSquare::a1,
              char type = 'k',
              Movesets *knight_movesets = nullptr,
              Movesets *king_movesets = nullptr
        );

        std::array<CMove, 32> getMoveset();
    private:
        enumColour colour_;
        enumSquare startingSquare_;
        enumPiece type_;

        // Pointers to the movesets initialised in CBoard
        Movesets *knight_movesets_;
        Movesets *king_movesets_;

        // The maximum number of moves any piece can have at one time is 27
        // This occurs with the queen located at any of the four center squares
        // Hence we can preallocate a size of 32 for the piece's moveset
        std::array<CMove, 32> moveset_;
};
