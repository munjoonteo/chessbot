#include "Piece.h"
#include "../types.h"

class NonSlidingPiece: Piece {
    public:
        NonSlidingPiece();
        void generateMoveset();
};
