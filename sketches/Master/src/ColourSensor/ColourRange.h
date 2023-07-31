#include "Colour.h"

#ifndef COLOURRANGE_H
#define COLOURRANGE_H

struct ColourRange
{
    public:
        ColourRange();
        ColourRange(Colour lower, Colour upper);
        ColourRange(int lr, int lg, int lb, int ur, int ug, int ub);

        Colour lowerColour;
        Colour upperColour;

        bool colourInRange(Colour col);
};
#endif