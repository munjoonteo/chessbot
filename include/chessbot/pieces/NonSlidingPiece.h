#include "CPiece.h"
#include "../types.h"

class NonSlidingPiece: CPiece {
    public:
        NonSlidingPiece();
        void generateMoveset();
};
