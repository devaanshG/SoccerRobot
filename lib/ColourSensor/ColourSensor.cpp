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
ColourRange ColourSensor::ranges[5] = *new ColourRange[5];

Adafruit_TCS34725 ColourSensor::sensor = new Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

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
    col = Colour(ColourSensor::r/512, ColourSensor::g/512, ColourSensor::b/512);//get RGB
    Serial.println(col.ToString());

    for(int i = 0; i < (sizeof(ranges)/sizeof(ranges[0])); i++){
        if(ranges[i].colourInRange(col)){
            return i;
        }
    }

    return -1;
}