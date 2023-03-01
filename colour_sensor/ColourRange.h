#include "Colour.h"

struct ColourRange
{
    public:
        ColourRange(Colour lower, Colour upper);
        ColourRange(int lr, int lg, int lb, int ur, int ug, int ub);

        Colour lowerColour;
        Colour upperColour;

        bool colourInRange(Colour col);
};