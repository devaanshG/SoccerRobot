#include "C:\Users\wdlea\programming\Arduino\soccerBot\lib\Magnetometer\magnetometer.h"
#include "C:\Users\wdlea\programming\Arduino\soccerBot\lib\Packets\packets.h"
#include "mutex.h"

//we will use both cores of the pico. 
//Core 0 will:
//Handle the peripherals and the other boards making it the only core
//using i2c which is probably good, becuase making our 
//own implementation of the protocol would be sub-optimal at best. 
//Core 1 will:
//Handle the game logic and any serial communication i may want to 
//implement, such as logging or a "CLI" for communication with the 
//robot.


//SLAVE 1
Mutex<MasterToSlave1*> ms1 = new Mutex(new MasterToSlave1);
bool ms1NeedsSend = false;

void SetMotors(float direction, unsigned short speed = 0xff, float rotation = 0, bool dribblerCapturing=true){
  ms1->moveSpeed = speed;
  ms1->moveRotation = rotation;
  ms1->moveDirection = direction;
  ms1->moveSpeed = speed;
}
void StopMotors(){
  SetMotors(0, 0);
}

//SLAVE 2
Mutex<Slave2ToMaster*> s2m = new Mutex(new Slave2ToMaster);
bool s2mNeedsSend = false;



//CORE 0
void SetupCore0(){
  
}
void DoGameLogic(){

}

//CORE 1
void SetupCore1(){

}

void CheckMagnetometer(){
  
}

void DeliverPackets(){
  if(ms1NeedsSend){
    ms1.GetLock();

    //deliver ms1
    ms1.object->Send();

    ms1.ReleaseLock();
  }
  if(s2mNeedsSend){
    s2m.GetLock();

    //request s2m
    s2m.object->Request();

    s2m.ReleaseLock();
  }
}

//arduino framework functions
void setup(){
  SetupCore0();
}
void setup1(){
  SetupCore1();
}

void loop(){
  DoGameLogic();
}
void loop1(){
  CheckMagnetometer();
  DeliverPackets();
}