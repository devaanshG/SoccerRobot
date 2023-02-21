#include "Arduino.h"
#include "Sensors.h"

Colour::Colour(int r, int g, int b){
    this->r = r;
    this->g = g;
    this->b = b;
}

ColourRange::ColourRange(Colour lower, Colour upper){
    this->lowerColour = lower;
    this->upperColour = upper;
}
ColourRange::ColourRange(int lr, int lg, int lb, int ur, int ug, int ub){
    this->lowerColour = new Colour(lr, lg, lb);
    this->upperColour = new Colour(ur, ug, ub);
}
ColourRange::colourInRange(Colour colour){
    return  colour.r > this->lowerColour.r && this->colour.r < upperColour.r &&
            colour.g > this->lowerColour.g && this->colour.g < upperColour.g &&
            colour.b > this->lowerColour.b && this->colour.b < upperColour.b;
}



ColourSensor::init(){
    ColourSensor::ranges = new ColourRange[] {new ColourRange(0, 0, 0, 255, 255, 255)};
    
    this->tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
}