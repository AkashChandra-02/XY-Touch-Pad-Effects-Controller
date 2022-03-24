/*
	UIUC ECE 110 Honors Lab Spring 2022
	Group 30
	Members: Akash Chandra & Asaiah Rock

	The touch screen code can be found here: https://github.com/adafruit/Adafruit_TouchScreen
	We are using bits of https://github.com/adafruit/Adafruit_TouchScreen/blob/master/examples/touchscreendemo/touchscreendemo.ino
*/

#include <stdint.h>
#include "TouchScreen.h"

#define NUM_POTS 4
//analogRead('a'+antenna)

#define NUM_C 4 
//analogWrite(motor, 0);

int x = 0;
int y = 0;
int z = 0;

int pot_value[4] = {0, 0, 0, 0};
int pot_pins = {A0, A1, A2, A3};
int out_pins = {3, 5, 6, 9};
int pressed = 0;
#define SCREEN_RES 300
#define DELAY_TIME 100

#define YP A4  // must be an analog pin, use "An" notation!
#define XM A5  // must be an analog pin, use "An" notation!
#define YM 8   // can be a digital pin
#define XP 9   // can be a digital pin
TouchScreen ts = TouchScreen(XP, YP, XM, YM, SCREEN_RES);

void setup() {
	
	for(int i = 0; i < NUM_C; i++)
	{
		pinMode(out_pins[i], OUTPUT);
	}

	Serial.begin(9600);

}

void loop() {
	
	//Read in analog values
	for(int i = 0; i < NUM_POTS; i++)
	{
		pot_value[i] = analogRead(pots_pin[i]);
	}
	
	//Modify the values if needed
	for(int i = 0; i < NUM_POTS; i++)
	{
		pot_value[i] = map(pot_value[i], 0, 1023, 0, 255);
	}
	
	//Write values out to PWM pins
	for(int i = 0; i < NUM_C; i++)
	{
		analogWrite(out_pins[i], pot_value[i]);
	}

	// a point object holds x y and z coordinates
  	TSPoint p = ts.getPoint();
  
  	// we have some minimum pressure we consider 'valid'
  	// pressure of 0 means no pressing!
  	if (p.z > ts.pressureThreshhold && pressed == 0) {

		x = p.x;
		y = p.y;
		pressed = 1;
		Serial.print("X = "); Serial.print(p.x);
     	Serial.print("\tY = "); Serial.print(p.y);
     	Serial.print("\tPressure = "); Serial.println(p.z);
  	}

	while(pressed == 1)
	{
		//Do something about it
		z = x + y;
		delay(DELAY_TIME);
		pressed = 0;
	}


}