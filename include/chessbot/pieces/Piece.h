#include <vector>

#include "../enums.h"

class Piece {
    public:
        Piece(enumColour colour, enumSquare startingSquare, char type);
        std::vector<enumSquare> getMoveset();
    private:
        enumColour colour_;
        enumPiece type_;
        enumSquare startingSquare_;
        std::vector<enumSquare> moveset_;
};
