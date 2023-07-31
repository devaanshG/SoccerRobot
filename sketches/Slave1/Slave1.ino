#include "C:/Users/wdlea/programming/Arduino/soccerBot/lib/Packets/packets.h"
#include "C:/Users/wdlea/programming/Arduino/soccerBot/lib/motor/Motors.h"
#include "Wire.h"

MasterToSlave1 MS1 = *new MasterToSlave1();

void setup(){
  Wire.begin(Slave1Address);
  Wire.onRecieve()
}

void onRecv(int count){
  MS1.Receive();
  MoveMotors(MS1.moveDirection, MS1.moveSpeed, MS1.moveRotation);

}
void SetDribbler(bool capturing){

}