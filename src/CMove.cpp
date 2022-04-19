#include "chessbot/constants.h"
#include "chessbot/CMove.h"


CMove::CMove(enumSquare from, enumSquare to, unsigned int flags) {
    auto fromUnsigned = unsigned(from);
    auto toUnsigned = unsigned(to);
    move_ = ((flags & 0xF) << 12) | ((fromUnsigned & 0x3F) << 6) | (toUnsigned & 0x3F);
}

unsigned int CMove::getTo() const {
    return move_ & 0x3F;
}

unsigned int CMove::getFrom() const {
    return (move_ >> 6) & 0x3F;
}

unsigned int CMove::getFlags() const {
    return (move_ >> 12) & 0xF;
}

void CMove::setTo(enumSquare to) {
    auto toUnsigned = unsigned(to);
    move_ &= ~0x3F; // Important to zero out the fields first
    move_ |= toUnsigned & 0x3F; // Make sure to & it to ensure only the required 6 bits are set
}

void CMove::setFrom(enumSquare from) {
    auto fromUnsigned = unsigned(from);
    move_ &= ~0xFC0;
    move_ |= (fromUnsigned & 0x3F) << 6;
}

void CMove::setFlags(unsigned int flags) {
    move_ &= ~0xF000;
    move_ |= (flags & 0xF) << 12;
}

bool CMove::isCapture() const {
    return (getFlags() & Constants::CAPTURE_FLAG) != 0;
}
