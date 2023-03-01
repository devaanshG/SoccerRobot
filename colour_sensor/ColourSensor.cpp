#include "Arduino.h"
#include "ColourSensor.h"

#include <Wire.h>
#include <Adafruit_LIS3MDL.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TCS34725.h"


void ColourSensor::init(){
   ranges[5] = ColourRange(0, 0, 0, 255, 255, 255);

    
    tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

    if(!tcs.begin()){
        Serial.println("tcs not found");
    }
}
void ColourSensor::update_colours(){
    tcs.getRawData(&r, &g, &b, &c);
}

int ColourSensor::get_current_colour_ID(){
    update_colours();
    Colour col = Colour(r/512, g/512, b/512);//get RGB
    Serial.println(col.ToString());

    for(int i = 0; i < sizeof(ranges); i++){
        if(ranges[i].colourInRange(col)){
            return i;
        }
    }

    return -1;
}