/*
 Example using the SparkFun HX711 breakout board with a scale
 By: Nathan Seidle
 SparkFun Electronics
 Date: November 19th, 2014
 License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).
 
 This example demonstrates basic scale output. See the calibration sketch to get the calibration_factor for your
 specific load cell setup.
 
 This example code uses bogde's excellent library: https://github.com/bogde/HX711
 bogde's library is released under a GNU GENERAL PUBLIC LICENSE
 
 The HX711 does one thing well: read load cells. The breakout board is compatible with any wheat-stone bridge
 based load cell which should allow a user to measure everything from a few grams to tens of tons.
 Arduino pin 2 -> HX711 CLK
 3 -> DAT
 5V -> VCC
 GND -> GND
 
 The HX711 board can be powered from 2.7V to 5V so the Arduino 5V power should be fine.
 
*/

#include "HX711.h"

#define calibration_factor 4492.0 //This value is obtained using the SparkFun_HX711_Calibration sketch

#define DOUT  3
#define CLK  2
int HEIGHTCOUNT  = 1  ;  
float TENHEIGHT[10]; 
float TENHEIGHTAVERAGE = 0.00;
float TENHEIGHTTOTAL = 0.0;
float LASTHEIGHT = 2;
HX711 scale(DOUT, CLK);

void setup() {
  Serial.begin(9600);
  Serial.println("MEASURE by Eir DEMO");

  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare();	//Assuming there is no weight on the scale at start up, reset the scale to 0

  Serial.println("Weight Readings:");
}

void loop() {
float b = scale.get_units() + 1; 
if (b < 2 && b != 1) scale.tare(); 
int c = b/LASTHEIGHT;
if (b < 2 && c < .1) {
  Serial.println("Scale Is Not Loaded"); 
  delay(2000);
}
else
{
  
Serial.println("CALCULATING WEIGHT"); 
int var = 0;
while(var < 10){
  TENHEIGHT[var] = scale.get_units();
  delay(500) ;
  var++;
}
 
  for(int i = 0 ; i < 10 ; i++){
  TENHEIGHTTOTAL = TENHEIGHTTOTAL+TENHEIGHT[i] ;
  }
TENHEIGHTAVERAGE = TENHEIGHTTOTAL / 10 ; 
  
 // Serial.print("The Average Weight Is: ");
 // Serial.print(scale.get_units(), 1); //scale.get_units() returns a float
 float check = TENHEIGHTAVERAGE + 2 - LASTHEIGHT;
 if (check < .5) {
   Serial.print(TENHEIGHTAVERAGE);
  Serial.print(" lbs"); //You can change this to kg but you'll need to refactor the calibration_factor
  Serial.println();
  Serial.println("PLEASE STEP OFF SCALE"); 
  delay(30000); 
 }
  LASTHEIGHT = TENHEIGHTAVERAGE + 2;
  TENHEIGHTTOTAL = 0;
  delay(1000); 
}
}
