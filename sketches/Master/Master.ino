//TARGETING Raspberry Pi Pico (NO wifi/bluetooth)

#include "mutex.h"
#include "Wire.h"
#include "C:/Users/wdlea/programming/Arduino/soccerBot/lib/Magnetometer/magnetometer.h"
#include "C:/Users/wdlea/programming/Arduino/soccerBot/lib/ColourSensor/ColourSensor.h"
#include "C:/Users/wdlea/programming/Arduino/soccerBot/lib/Packets/packets.h"

//i will use both cores of the pico. 
//Core 0 will:
//Handle the peripherals and the other boards making it the only core
//using i2c which is probably good, becuase making our 
//own implementation of the protocol would be sub-optimal at best. 
//Core 1 will:
//Handle the game logic and any serial communication i may want to 
//implement, such as logging or a "CLI" for communication with the 
//robot.


//SLAVE 1
Mutex<MasterToSlave1*> ms1 = *new Mutex(new MasterToSlave1);
volatile bool ms1NeedsSend = false;


void SetMotors(float direction, unsigned short speed = 0xff, float rotation = 0, bool dribblerCapturing=true){
  ms1.object->moveSpeed = speed;
  ms1.object->moveRotation = rotation;
  ms1.object->moveDirection = direction;
  ms1.object->moveSpeed = speed;
}

void StopMotors(){
  SetMotors(0, 0);
}

//SLAVE 2
Mutex<Slave2ToMaster*> s2m = *new Mutex(new Slave2ToMaster);
volatile bool s2mNeedsSend = false;

//MAGNETOMETER
Magnetometer mag = *new Magnetometer();
Mutex<float> heading = *new Mutex<float>(0);

//COLOUR SENSOR
ColourSensor col = *new ColourSensor();
Mutex<int> colourID = *new Mutex<int>(0);

//CORE 0
void SetupCore0(){
  Serial.begin(9600);
}
void DoGameLogic(){
  Serial.print(F("\tCOLID:\t"));
  colourID.GetLock();
  Serial.print(colourID.object);
  colourID.ReleaseLock();

  Serial.print(F("\tHEADING:\t"));
  heading.GetLock();
  Serial.print(heading.object);
  heading.ReleaseLock();

  //S2M
  s2m.GetLock();
  Serial.print(F("\tESTIMATEDBALLDIRECTION:\t"));
  Serial.print(s2m.object->estimatedBallDirection);

  Serial.print(F("\tLEFTDISTANCE:\t"));
  Serial.print(s2m.object->leftObsticalDistance);

  Serial.print(F("\tRIGHTDISTANCE:\t"));
  Serial.print(s2m.object->rightObsticalDistance);

  s2m.ReleaseLock();
}

//CORE 1
void SetupCore1(){
  Wire.begin();
  Wire.setSDA(0);
  Wire.setSCL(1);

  mag.Init();
  col.init();
}

void CheckI2CPeripherals(){
  heading.GetLock();
  heading.object = mag.GetHeading();
  heading.ReleaseLock();

  colourID.GetLock();
  colourID.object = col.get_current_colour_ID();
  colourID.ReleaseLock();
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
  CheckI2CPeripherals();
  DeliverPackets();
}