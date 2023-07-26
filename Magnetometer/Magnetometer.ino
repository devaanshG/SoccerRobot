#include "magnetometer.h"

//debugging purpouses
#include <WiFi.h>

void setup(){
  Wire.setSDA(0);
  Wire.setSCL(1);
  
  Serial.begin(9600);
  if(!Magnetometer::Init()){
    Serial.println("Magnetometer failed to start");
    while(1){}
  }
}
void loop(){
  Serial.println(Magnetometer::GetHeading());
  delay(100);
}