#include "magnetometer.h"
#include <math.h>

Adafruit_LIS3MDL* Magnetometer::compass = new Adafruit_LIS3MDL();//fixed wooooooooooo

float Magnetometer::GetHeading(){
    sensors_event_t event; 
    Magnetometer::compass->getEvent(&event);

    float x = event.magnetic.x;
    float y = event.magnetic.y;

    if(y>0){
      return 90 - atan(x/y)*180/PI;
    }else if(y<0){
      return 270 - atan(x/y)*180/PI;
    }else if(y == 0 && x < 0){
      return 180;
    }else if(y == 0 && x >= 0){
      return 0;
    }

    return -1;
}
bool Magnetometer::Init(){
    Magnetometer::compass = new Adafruit_LIS3MDL();

    bool sucess = Magnetometer::compass->begin_I2C();
    Magnetometer::compass->setPerformanceMode(LIS3MDL_ULTRAHIGHMODE);
    Magnetometer::compass->setIntThreshold(500);
    Magnetometer::compass->configInterrupt(false, false, true, // enable z axis
        true, // polarity
        false, // don't latch
        true); // enabled!
    return sucess;
}