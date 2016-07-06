/*
 Edited the orginal calibration script by Nathan Seidle to run automatically with minimal input. 
 By: Harvey Scholl
 Eir Health Systems
 Date:  July 5th, 2016
 License:  Public Domain
 
 This is the calibration sketch. Use it to determine the calibration_factor that the main example uses. It also
 outputs the zero_factor useful for projects that have a permanent mass on the scale in between power cycles.
 
 Setup your scale and start the sketch WITHOUT a weight on the scale
 Once readings are displayed place the weight on the scale
 Press +/- or a/z to adjust the calibration_factor until the output readings match the known weight
 Use this calibration_factor on the example sketch
 
 This example assumes pounds (lbs). If you prefer kilograms, change the Serial.print(" lbs"); line to kg. The
 calibration factor will be significantly different but it will be linearly related to lbs (1 lbs = 0.453592 kg).
 
 Your calibration factor may be very positive or very negative. It all depends on the setup of your scale system
 and the direction the sensors deflect from zero state
 This example code uses bogde's excellent library: https://github.com/bogde/HX711
 bogde's library is released under a GNU GENERAL PUBLIC LICENSE
 Arduino pin 2 -> HX711 CLK
 3 -> DOUT
 5V -> VCC
 GND -> GND
 
 Most any pin on the Arduino Uno will be compatible with DOUT/CLK.
 
 The HX711 board can be powered from 2.7V to 5V so the Arduino 5V power should be fine.
 
*/

#include "HX711.h"

#define DOUT  3
#define CLK  2

HX711 scale(DOUT, CLK);

float calibration_factor = -100000; //Go as low as you'd like to start 
int target_weight = 0; //This is the known weight we are trying to get to


void setup() {
  Serial.begin(9600);
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("Taring The Scale");
  scale.set_scale();
  scale.tare();	//Reset the scale to 0
  Serial.println("Taring Complete");
  Serial.println("Place known weight on scale");
  
  

  

  long zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
  Serial.println("Enter the weight in pounds");
}

void loop() {

if(Serial.available())
  {target_weight = Serial.parseInt();
Serial.print("Calibratimg with target weight of ");
Serial.println(target_weight);  
  }
while(target_weight > 0){
scale.set_scale(calibration_factor); //Adjust to this calibration factor
float a = (scale.get_units() - target_weight);
a = abs(a);
if(a <= 1 && a >= 0 ) {
Serial.println("Target Weight Reached with Calibration Value of ");
Serial.print(calibration_factor);
int target_weight = 0;
}
else
{
calibration_factor += 1;
Serial.print(scale.get_units() - target_weight);
Serial.print(":");
Serial.println(calibration_factor);
}
} 
}
