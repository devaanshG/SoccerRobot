#include "Adafruit_TCS34725.h"
#include "Colour.h"
#include "ColourRange.h"


#ifndef COLOURSENSOR_H
#define COLOURSENSOR_H

class ColourSensor{
    public:
        static ColourRange ranges[17];

        static void init();
        static int get_current_colour_ID();
    private:
        static uint16_t r, g, b, c;
        static Adafruit_TCS34725 tcs;

        static void update_colours();
};

#endif