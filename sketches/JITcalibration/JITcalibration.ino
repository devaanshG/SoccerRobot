#include "src/Magnetometer/magnetometer.h"

void setup() {
  // put your setup code here, to run once:
  Magnetometer::Init();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(Magnetometer::GetHeading());
}
