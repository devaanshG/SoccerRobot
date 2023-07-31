#include "Adafruit_TCS34725.h"
#include <Adafruit_Sensor.h>
#include "Colour.h"
#include "ColourRange.h"


#ifndef COLOURSENSOR_H
#define COLOURSENSOR_H

class ColourSensor{
    public:
        static ColourRange ranges[5];


        //initailizes colour sensors
        static void init();
        
        static int get_current_colour_ID();
        

        static Colour col;
        static uint16_t r, g, b, c;
    private:

        
        static Adafruit_TCS34725 sensor;

        static void update_colours();
};

#endif