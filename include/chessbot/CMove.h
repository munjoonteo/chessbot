#include "enums.h"

class CMove {
    public:
        CMove(enumSquare from = enumSquare::a1,
              enumSquare to = enumSquare::a1,
              unsigned int flags = 0
        );

        unsigned int getTo() const;
        unsigned int getFrom() const;
        unsigned int getFlags() const;

        void setTo(enumSquare to);
        void setFrom(enumSquare from);
        void setFlags(unsigned int flags);

        bool isCapture() const;
    private:
        unsigned int move_;
};