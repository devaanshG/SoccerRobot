#include "magnetometer.h"

void setup(){
  
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