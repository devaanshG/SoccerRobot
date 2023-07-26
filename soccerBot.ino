#include "Wire.h"
#include "C:\Users\wdlea\programming\Arduino\soccerBot\ColourSensor\ColourSensor.cpp"
#include "Magnetometer/magnetometer.cpp"
#include "ColourSensor/ColourRange.cpp"
#include "ColourSensor/Colour.cpp"
#include "motor/Motors.cpp"

const char BALL_MICROSWITCH_PIN = 0;
const char BALL_MICROSWITCH_ACTIVE = HIGH;

bool GetBallMicroswitchState(){
  return digitalRead(BALL_MICROSWITCH_PIN) == BALL_MICROSWITCH_ACTIVE;
}

Colour currentCol;
float currentHeading;
void setup() {
  Serial.begin(9600);
  // Configure pins
  

  // Configure I2C bus
  Wire.setSDA(0);
  Wire.setSCL(1);
  Wire.begin();


  //initialize libraries
  ColourSensor::init();
  Magnetometer::Init();
  Motors::init();
}


void CalibrateStage1(){
  //the robot should be facing the opponents goal 
}

void loop() {
  // Update all sensors
  ColourSensor::get_current_colour_ID();
  currentCol = ColourSensor::col;
  currentHeading = Magnetometer::GetHeading();


  Serial.println(currentCol.ToString() + " " + String(currentHeading));
  
  Motors::MoveMotors(0.0, 255, 0.0);

  // Check if ball is in posession
  bool isTouchingBall = GetBallMicroswitchState();
  
  // If true, navigate to goal


  // Else, find ball
  // Take possesion of ball
  // Navigate to goal
}
