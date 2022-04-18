#include <vector>

#include "../enums.h"

class Piece {
    public:
        Piece(enumColour colour = enumColour::white,
              enumSquare startingSquare = enumSquare::a1,
              char type = 'k'
        );
        std::vector<enumSquare> getMoveset();
    private:
        enumColour colour_;
        enumSquare startingSquare_;
        enumPiece type_;
        std::vector<enumSquare> moveset_;
};
