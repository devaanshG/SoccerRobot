#include "magnetometer.h"
#include <math.h>
Adafruit_LIS3MDL* Magnetometer::compass = new Adafruit_LIS3MDL();

const float HARD_IRON[3] = {-16.72, -7.68, -50.15};//CONSIDER that these are placeholder values

float Magnetometer::GetHeading(){
    sensors_event_t event; 
    Magnetometer::compass->getEvent(&event);


    Serial.print(" X:");
    Serial.print(event.magnetic.x);
    Serial.print(" Y:");
    Serial.print(event.magnetic.y);
    Serial.print(" Z:");
    Serial.println(event.magnetic.z);

    //ASSUMING that i can just modify these
    event.magnetic.x -= HARD_IRON[0];//CONSIDER that i dont think -= is right, but the example code uses this
    event.magnetic.y -= HARD_IRON[1];
    event.magnetic.z -= HARD_IRON[2];//parrelell to ground(in the robots world, the earth seems flat)

    return atan2(event.magnetic.x, event.magnetic.y) * 180 / M_PI;
}
bool Magnetometer::Init(){
    Magnetometer::compass = new Adafruit_LIS3MDL();

    bool sucess = Magnetometer::compass->begin_I2C(0x1C);
    Magnetometer::compass->setPerformanceMode(LIS3MDL_ULTRAHIGHMODE);
    Magnetometer::compass->setIntThreshold(500);
    Magnetometer::compass->configInterrupt(true, true, true,//false, false, true, // enable z axis
        true, // polarity
        false, // don't latch
        true); // enabled!
    return sucess;
}