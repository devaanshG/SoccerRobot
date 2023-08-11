#include <Arduino.h>
#include "BallSensor.h"

#define IR1 A0
#define IR2 A1
#define IR3 A2
#define IR4 A3

#define BALL 13

int velWeight = 2.4;
int ballDir = 0;
int ballDelta;
int ballVel;

int prevDir = 0;

float DeltaTime(){
  static int lastTime;
  int curTime = millis();
  int delta = curTime - lastTime;
  lastTime = curTime;
  return delta;
}

void Init() {

}

int getBallDir() {
  // put your main code here, to run repeatedly:
  if (map(analogRead(IR1), 1023, 300, 0, 100) == 0 && map(analogRead(IR2), 1023, 300, 0, 100) == 0 && map(analogRead(IR3), 1023, 300, 0, 100) == 0 && map(analogRead(IR4), 1023, 300, 0, 100) == 0) {
    Serial.println("BALL NOT FOUND");
    return NULL_VALUE;
  } else {
    int sensor1Reading = map(analogRead(IR1), 1023, 300, 0, 100);
    int sensor2Reading = map(analogRead(IR2), 1023, 300, 0, 100);
    int sensor3Reading = map(analogRead(IR3), 1023, 300, 0, 100);
    int sensor4Reading = map(analogRead(IR4), 1023, 300, 0, 100);

    ballDir = sensor1Reading * 90.0f / 100.0f + sensor2Reading * 30.0f / 100.0f + sensor3Reading * -30.0f / 100.0f + sensor4Reading * -90.0f / 100.0f; // Find the sensor with the highest reading (I.e. the sensor that is most proximal to the ball)
    ballDir = map(ballDir, -30, 30, -70, 70);

    ballDelta = ballDir - prevDir; // Find
    ballVel = ballDelta - DeltaTime();

    int motorsDir = ballDir + ballVel * velWeight;
    return motorsDir;
  }   
}
