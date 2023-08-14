#include "src/BallSensor/BallSensor.h"
#include "src/ColourSensor/ColourSensor.h"
#include "src/Magnetometer/magnetometer.h"
#include "src/motor/Motors.h"

const int GOAL_HEADING = ;

enum FieldColour{
  OutWhite,
  GoalBlack,
  LightGreen,
  DarkGreen,
  MidfieldGreen
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ColourSensor::init();
  Motors::init();
  Magnetometer::Init();
  while(!Serial) {
    delay(10);
  }
  Serial.println("<------ SELF RIGHTING TEST ------>");
}

void loop() {
  // put your main code here, to run repeatedly:
  int COL = ColourSensor::get_current_colour_ID();
  int theta = (int)Magnetometer::GetHeading();

  Serial.print("COLOUR: ");
  Serial.print(COL);
  Serial.print(" HEADING: ");
  Serial.println(theta);
  while(COL != (int)FieldColour::GoalBlack) {
    int theta = (int)Magnetometer::GetHeading();
    Motors::MoveMotors(-(90+theta), 255, 0);
  }

  while (theta != GOAL_HEADING) {
      if (theta < GOAL_HEADING) {
        Motors::MoveMotors(0, 0, 255);
      } else {
        Motors::MoveMotors(0, 0, -255);
      }
    }
}
