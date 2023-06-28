#include "Motors.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Motors::init();
}

unsigned short direction = 0;

void loop() {
  for (int i = 0; i<=255; i++){

    Motors::MoveMotors(0, i, 0);
    Serial.println(i);
    delay(10);
  }
  delay(500);
}
