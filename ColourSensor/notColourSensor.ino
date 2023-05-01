#include "ColourSensor.h"

void setup(){
    Serial.begin(9600);
    ColourSensor::init();
}
void loop(){
    ColourSensor::get_current_colour_ID();
    Serial.println(ColourSensor::col.ToString());
}