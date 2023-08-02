#include "src\ColourSensor\ColourSensor.h"

void setup(){
    Wire.setSDA(0);
    Wire.setSCL(1);
    Wire.begin();
    
    Serial.begin(9600);
    // while(!Serial);
    ColourSensor::init();
}

void loop(){
    ColourSensor::get_current_colour_ID();
    Serial.println(ColourSensor::col.ToString());
    delay(100);
}