#include "Arduino.h"
#include <Adafruit_LIS3MDL.h>
#include <Adafruit_Sensor.h>

#ifndef MAGNETOMETER_H
#define MAGNETOMETER_H

class Magnetometer{
    public:

        static float GetHeading();
        static bool Init();
    private:
        static Adafruit_LIS3MDL* compass;
};

#endif