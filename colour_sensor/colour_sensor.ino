#include <Wire.h>
#include <Adafruit_LIS3MDL.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
Adafruit_LIS3MDL compass;

uint16_t r, g, b, c;
int x, y;

String colours[]                          = {"GOAL",    "LEFT",     "RIGHT",    "MIDDLE"};
uint16_t lower_range[sizeof(colours)][3]  = {{0, 0, 0}, {0, 0, 0},  {0, 0, 0},  {0, 0, 0}};
uint16_t upper_range[sizeof(colours)][3]  = {{0, 0, 0}, {0, 0, 0},  {0, 0, 0},  {0, 0, 0}};
void setup(){
  Serial.begin(9600);
  if(!tcs.begin()){while(true){
      Serial.println("tcs not found");
    }
  }
  if(!compass.begin_I2C()){
    while(true){
      Serial.println("compass not found");
    }
  }
  compass.setPerformanceMode(LIS3MDL_ULTRAHIGHMODE);
  compass.setIntThreshold(500);
  compass.configInterrupt(false, false, true, // enable z axis
                          true, // polarity
                          false, // don't latch
                          true); // enabled!
}

void loop(){
  compass.read();
  
  update_colours();
  int c = get_current_colour_ID();
  Serial.print(c != -1 ? colours[c] : String(c));
  Serial.println(" R" + String(r/512) + " G" + String(g/512) + " B" + String(b/512) + " Z" + compass.z);
}
void update_colours(){
  tcs.getRawData(&r, &g, &b, &c);
}

int get_col_id(String col){
  for(int i = 0; i < sizeof(colours); i++){
    if(colours[i] == col){
      return i;
    }
  }
  return -1;
}

int get_current_colour_ID(){
  int col_arr[3] = {r/512, g/512, b/512};//get RGB
  for(int i = 0; i<sizeof(colours); i++){
    bool match = true;
    for(int chan = 0; chan<3; chan++){
      if(!(lower_range[i][chan] < col_arr[chan] and upper_range[i][chan] > col_arr[chan])){
         match = false;
         break;
      }
    }
    if(match){
      return i;
    }
  }
  return -1;
}

void update_position(){
  
}
