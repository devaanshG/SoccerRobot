#include "Motors.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Motors::init();
}

unsigned short direction = 0;

void loop() {
  for (int direction = 0; direction<=360; direction++){

    Motors::MoveMotors(0, 255, 100);
    delay(100);
  }
  delay(500);
}
