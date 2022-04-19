#include <vector>

#include "enums.h"
#include "CMove.h"

class CPiece {
    public:
        CPiece(enumColour colour = enumColour::white,
              enumSquare startingSquare = enumSquare::a1,
              char type = 'k'
        );

        std::vector<CMove> getMoveset();
    private:
        enumColour colour_;
        enumSquare startingSquare_;
        enumPiece type_;
        std::vector<CMove> moveset_;
};
