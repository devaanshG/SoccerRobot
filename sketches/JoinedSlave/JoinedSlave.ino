#include "src/Packets/packets.h"
#include "src/BallSensor/BallSensor.h"
#include "Wire.h"
#include <NewPing.h>
#include "./src/motor/Motors.h"

#define DRIBBLER_EN 11
#define DRIBBLER_PH 12

#define DRIBBLER_IDLE_EN 0
#define DRIBBLER_ACTIVE_EN 255

#define MAX_DISTANCE 300//cm
#define LEFT_SONAR_PIN 1
#define RIGHT_SONAR_PIN 2

MasterToSlave1 MS1 = *new MasterToSlave1();


NewPing leftSonar(LEFT_SONAR_PIN, LEFT_SONAR_PIN, MAX_DISTANCE);
NewPing rightSonar(RIGHT_SONAR_PIN, RIGHT_SONAR_PIN, MAX_DISTANCE);

void setup(){
  Wire.begin(SlaveAddress);
  Init();
  Wire.onReceive(OnRecv);
  Wire.onRequest(OnReq);

  Motors::init();

  pinMode(DRIBBLER_EN, OUTPUT);
  pinMode(DRIBBLER_PH, OUTPUT);
}

Slave2ToMaster pak = *new Slave2ToMaster();

void loop(){
  pak.estimatedBallDirection = getBallDir();
  DoPings();//two cores would be nice becuase pings take ages and i dont want to create my own library using ISRs
}

void DoPings(){
	pak.leftObsticalDistance = leftSonar.ping_cm();
  pak.rightObsticalDistance = rightSonar.ping_cm();
}

void OnReq(int count){
	pak.Respond(count);
}

void OnRecv(int count){
  MS1.Recieve();
  Motors::MoveMotors(MS1.moveDirection, MS1.moveSpeed, MS1.moveRotation);
  SetDribbler(MS1.dribblerOn, MS1.dribblerCapturing);
}

void SetDribbler(bool on, bool capturing){
  analogWrite(DRIBBLER_EN, on ? DRIBBLER_ACTIVE_EN : DRIBBLER_IDLE_EN);
  digitalWrite(DRIBBLER_PH, (int)capturing);
}