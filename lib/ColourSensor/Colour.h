#include "Arduino.h"

#ifndef COLOUR_H
#define COLOUR_H 

struct Colour
{
    public:
        Colour(int r, int g, int b);
        Colour();
        uint16_t r, g, b;
        String ToString();
};

#endif