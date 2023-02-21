#include "Motors.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Motors::init();
}

void loop() {
  for (int i = 0; i<=255; i++){
    Motors::MoveMotors(0, i, 0);
    delay(10);
  }
  delay(500);
}
