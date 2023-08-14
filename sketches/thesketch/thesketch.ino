#include "src/BallSensor/BallSensor.h"
#include "src/ColourSensor/ColourSensor.h"
#include "src/Magnetometer/magnetometer.h"
#include "src/motor/Motors.h"

#include "calibrationConstants.h"

#define BALL_SENSOR_PIN 13

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Motors::init();
  ColourSensor::init();
  Magnetometer::Init();

  pinMode(13, INPUT);
}



void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(HasBall());
  if(!DoAttack()){
    DoDefend();
  }
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

bool DoAttack() {
  // Check if we are in the field
  if(InField()){
    int ballHeading = GetBallHeading();
    if(ballHeading == 1000){
      return false;//defend
    }
    
    if(HasBall()){
      int goalHeading = EstimateOpponentGoalHeading();
      Motors::MoveMotors(
         ballHeading, 
         255, 
         0);

    }else{
       Motors::MoveMotors(
         ballHeading, 
         255, 
         0);
    }
    return true;
  }else{
    ReturnToField();
  }
};

void DoDefend(){
  Motors::MoveMotors(EstimateOurGoalHeading(), 255, 0);
}

int GetBallHeading(){
  return getBallDir();
}


enum FieldColour{
  OutWhite,
  GoalBlack,
  LightGreen,
  DarkGreen,
  MidfieldGreen
};

int EstimateOurGoalHeading(){
  int estimate = 360 - downfieldHeading;
  if(ColourSensor::get_current_colour_ID() == leftGreenID){
    estimate -= 45;
  }else if(ColourSensor::get_current_colour_ID() == rightGreenID){
    estimate += 45;
  }
  return estimate;
}

int EstimateOpponentGoalHeading(){
  int estimate = downfieldHeading;
  if(ColourSensor::get_current_colour_ID() == leftGreenID){
    estimate += 45;
  }else if(ColourSensor::get_current_colour_ID() == rightGreenID){
    estimate -= 45;
  }
  return estimate;
}

bool InMiddle(){
  return ColourSensor::get_current_colour_ID() == (int)MidfieldGreen;
}

bool InGoal(){
  return ColourSensor::get_current_colour_ID() == (int)GoalBlack;
}

bool InField() {
  return ColourSensor::get_current_colour_ID() != (int)OutWhite;
}

void ReturnToField(){

}

bool HasBall(){
  return digitalRead(13) == LOW;
}