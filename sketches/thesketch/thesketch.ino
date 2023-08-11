#include "src\BallSensor\BallSensor.h"
#include "src\ColourSensor\ColourSensor.h"
#include "src\Magnetometer\magnetometer.h"
#include "src\motor\Motors.h"



#define BALL_SENSOR_PIN 13

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Motors::init();
  ColourSensor::init();
  Magnetometer::Init();
}



void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(HasBall());
  // if(HasBall()){
  //   DoAttack();
  // }else{
  //   int heading = GetBallHeading();
  //   if(heading == 1000){//note that this amy change
  //     MoveToGoal();
  //   }else{
  //     Move(heading);
  //   }
  // }
}

bool HasBall() {
    return digitalRead(BALL_SENSOR_PIN) ? true:false;
};

bool DoAttack() {
  // Check if we are in the field
  if(InField()){
    int ballHeading = GetBallHeading();
    if(ballHeading == 1000){
      return false;//defend
    }
    
    // If GoToBall();
      // GoToGoal
    // If !GoToBall();
      // return
  // If not in field
    // Move into field
    // Loop back
  }
};

bool GoToBall() {
  if(InField()){
    
    // If ball not found
      // Return
    // Else
      // While !HasBall Follow ball
      // Retur
  // If not in field
    // Move into field
  }
    
};

bool GoToGoal() {
  
};

int GetBallHeading();
void Move(int heading);
void MoveToGoal();


enum FieldColour{
  OutWhite
  GoalBlack,
  LightGreen,
  DarkGreen,
  MidfieldGreen
}

bool InMiddle(){
  return ColourSensor::get_current_colour_ID() == (int)MidfieldGreen
}

bool InGoal(){
  return ColourSensor::get_current_colour_ID() == (int)GoalBlack;
}
bool InField() {
  return ColourSensor::get_current_colour_ID() != (int)OutWhite;
};