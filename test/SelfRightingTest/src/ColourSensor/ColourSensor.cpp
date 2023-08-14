#include "Arduino.h"
#include "ColourSensor.h"

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TCS34725.h"

uint16_t ColourSensor::r = 0;
uint16_t ColourSensor::g = 0;
uint16_t ColourSensor::b = 0;
uint16_t ColourSensor::c = 0;
Colour ColourSensor::col = Colour();

Colour ColourSensor::colours[5] = {
    *new Colour(5029, 7977, 9186),//outside
    *new Colour(457, 590, 697),//goal black
    *new Colour(2229, 3391, 2339),//green 1
    *new Colour(1744, 3350, 2660),//green 2
    *new Colour(546, 919, 1027)//midfield
};

Adafruit_TCS34725 ColourSensor::sensor = *new Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

void ColourSensor::init(){

    
    sensor = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

    if(!sensor.begin(41, &Wire)){
        Serial.println("tcs not found");
    }

    
}
void ColourSensor::update_colours(){
    ColourSensor::sensor.getRawData(&r, &g, &b, &c);
}

int ColourSensor::get_current_colour_ID(){
    update_colours();
    col = Colour(ColourSensor::r, ColourSensor::g, ColourSensor::b);//get RGB
    Serial.println(col.ToString());

    int minDist = 0xFFFFFFFF;
    int closestCol = -1;
    for(int i = 0; i < 5; i++){
        int dist = col.DistanceFrom(colours[i]);
        if(dist < minDist){
            closestCol = i;
            minDist = dist;
        }
    }

    const int ColourMaximumDistance = 0xFFFFFFF;//big number, this is just here in case we need to do something to do with filtering out other colours later
    return (minDist < ColourMaximumDistance ? closestCol : -1);
}