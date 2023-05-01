#include "Wire.h"
#include "C:\Users\wdlea\programming\Arduino\soccerBot\ColourSensor\ColourSensor.cpp"
#include "Magnetometer/magnetometer.cpp"
#include "ColourSensor/ColourRange.cpp"
#include "ColourSensor/Colour.cpp"

Colour currentCol;
float currentHeading;
void setup() {
  Serial.begin(9600);
  // Configure pins

  // Configure I2C bus
  Wire.begin();

  //initialize libraries
  ColourSensor::init();
  Magnetometer::Init();
}



void loop() {
  // Update all sensors
  ColourSensor::get_current_colour_ID();
  currentCol = ColourSensor::col;
  currentHeading = Magnetometer::GetHeading();


  Serial.println(currentCol.ToString() + " " + String(currentHeading));

  // Check if ball is in posession

  // If true, navigate to goal


  // Else, find ball
  // Take possesion of ball
  // Navigate to goal
}