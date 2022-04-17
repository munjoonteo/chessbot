#include <vector>

#include "../enums.h"

class Piece {
    public:
        Piece();
        std::vector<enumSquare> getMoveset();
    private:
        enumPiece colour;
        enumPiece type;
        std::vector<enumSquare> moveset;
};
