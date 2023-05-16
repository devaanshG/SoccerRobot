#include "Motors.h"
#include "Arduino.h"

#define EN1 5
#define EN2 6
#define EN3 3

#define PH1 4
#define PH2 7
#define PH3 2

void Motors::MoveMotors(float theta, int speed, float angle){
  if(speed < 0 || speed > 255){
    Serial.println("Error: invalid MoveMotors speed input");
    return;
  }

  float angle1 = (30 + theta) * PI/180;
  float angle2 = (150 + theta) * PI/180;
  float angle3 = (90 + theta) * PI/180;
    
  float speed1 = cos(angle1) * speed + angle;
  float speed2 = cos(angle2) * speed + angle;
  float speed3 = cos(angle3) * speed + angle;

  MoveMotor(0, speed1);
  MoveMotor(1, speed2);
  MoveMotor(2, speed3);
}

void Motors::MoveMotor(int motor, float speed){
    int phPin;
    int enPin;

    switch (motor)
    {
        case 0:
            phPin = PH1;
            enPin = EN1;
            break;
        case 1:
            phPin = PH2;
            enPin = EN2;
            break;
        case 2:
            phPin = PH3;
            enPin = EN3;
            break;
    }
    digitalWrite(phPin, speed < 0 ? 1 : 0);
    analogWrite(enPin, abs(speed));
}

void Motors::init(){
    pinMode(EN1, OUTPUT);
    pinMode(EN2, OUTPUT);
    pinMode(EN3, OUTPUT);
    pinMode(PH1, OUTPUT);
    pinMode(PH2, OUTPUT);
    pinMode(PH3, OUTPUT);
}