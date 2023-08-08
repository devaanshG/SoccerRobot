#include "src/Packets/packets.h"
#include "src/BallSensor/BallSensor.h"
#include "Wire.h"
#include <NewPing.h>

#define MAX_DISTANCE 300//cm
#define LEFT_SONAR_PIN 1
#define RIGHT_SONAR_PIN 2

NewPing leftSonar(LEFT_SONAR_PIN, LEFT_SONAR_PIN, MAX_DISTANCE);
NewPing rightSonar(RIGHT_SONAR_PIN, RIGHT_SONAR_PIN, MAX_DISTANCE);

void setup(){
  Wire.begin(Slave2Address);
  Init();
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