#include "C:/Users/wdlea/programming/Arduino/soccerBot/lib/Packets/packets.h"
#include "C:/Users/wdlea/programming/Arduino/soccerBot/lib/motor/Motors.h"
#include "Wire.h"

MasterToSlave1 MS1 = *new MasterToSlave1();

#define DRIBBLER_EN 1
#define DRIBBLER_PH 2

#define DRIBBLER_IDLE_EN 0
#define DRIBBLER_ACTIVE_EN 255

void setup(){
  Wire.begin(Slave1Address);
  Wire.onReceive(onRecv);

  Motors::init();

  pinMode(DRIBBLER_EN, OUTPUT);
  pinMode(DRIBBLER_PH, OUTPUT);
}

void onRecv(int count){
  MS1.Recieve();
  Motors::MoveMotors(MS1.moveDirection, MS1.moveSpeed, MS1.moveRotation);
  SetDribbler(MS1.dribblerOn, MS1.dribblerCapturing);
}

void SetDribbler(bool on, bool capturing){
  analogWrite(DRIBBLER_EN, on ? DRIBBLER_ACTIVE_EN : DRIBBLER_IDLE_EN);
  analogWrite(DRIBBLER_PH, (int)capturing);
}