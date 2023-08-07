//TARGETING Raspberry Pi Pico (NO wifi/bluetooth)

#include "mutex.h"
#include "Wire.h"
#include "src/Magnetometer/magnetometer.h"
#include "src/ColourSensor/ColourSensor.h"
#include "src/Packets/packets.h"

#define CALIBRATE_BUTTON_PIN 7 //both must support ISR(i think all rpi pins support)
#define PLAY_BUTTON_PIN 8

#define BUTTON_DEBOUNCE_DURATION 100//ms

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
Mutex<MasterToSlave1> ms1 = *new Mutex(new MasterToSlave1);
volatile bool ms1NeedsSend = false;


void SetMotors(float direction, unsigned short speed = 0xff, float rotation = 0, bool dribblerCapturing=true, bool dribblerOn = true){
  ms1.GetLock();
  ms1.object->moveSpeed = speed;
  ms1.object->moveRotation = rotation;
  ms1.object->moveDirection = direction;
  ms1.object->moveSpeed = speed;
  ms1.object->dribblerOn = dribblerOn;
  ms1.ReleaseLock();
}

void StopMotors(){
  SetMotors(0, 0, 0, true, false);
}

//SLAVE 2
Mutex<Slave2ToMaster> s2m = *new Mutex(new Slave2ToMaster);
volatile bool s2mNeedsSend = false;

//MAGNETOMETER
Magnetometer mag = *new Magnetometer();
Mutex<int> heading = *new Mutex<int>(0);

//COLOUR SENSOR
ColourSensor col = *new ColourSensor();
Mutex<int> colourID = *new Mutex<int>(0);

//STATE
bool isPlaying = false;
int attackHeading = 0;

//HELPERS
bool IsGoingAttackDirection(){
  return heading.object > (attackHeading - 90)%360 && heading.object < (attackHeading + 90)%360;//not very good but an atomic operation so it will be fine
}

//INTERRUPTS
void OnCalibrateRise(){
  static int lastPress;
  int currentTime = millis();
  if(currentTime - lastPress > BUTTON_DEBOUNCE_DURATION){
    heading.GetLock();
    attackHeading = heading.object;
    heading.ReleaseLock();
  }
  lastPress = currentTime;
}

void OnPlayRise(){
  static int lastPress;
  int currentTime = millis();
  if(currentTime - lastPress > BUTTON_DEBOUNCE_DURATION){
    isPlaying = !isPlaying;
  }
  lastPress = currentTime;
}

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

  pinMode(PLAY_BUTTON_PIN, INPUT_PULLDOWN);
  pinMode(CALIBRATE_BUTTON_PIN, INPUT_PULLDOWN);

  attachInterrupt(digitalPinToInterrupt(PLAY_BUTTON_PIN), OnPlayRise, RISING);
  attachInterrupt(digitalPinToInterrupt(CALIBRATE_BUTTON_PIN), OnCalibrateRise, RISING);
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
  if(isPlaying)
    DoGameLogic();
  else
    StopMotors();
}
void loop1(){
  CheckI2CPeripherals();
  DeliverPackets();
}