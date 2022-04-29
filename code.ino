/*
	UIUC ECE 110 Honors Lab Spring 2022
	Group 30
	Members: Akash Chandra & Asaiah Rock

	The touch screen code can be found here: https://github.com/adafruit/Adafruit_TouchScreen
	We using the same method to read the screen as https://github.com/adafruit/Adafruit_TouchScreen/blob/master/examples/touchscreendemo/touchscreendemo.ino
*/

#include <stdint.h>
#include "TouchScreen.h"
//numberof  
#define NUM_POTS 4

//Number of outputs, number_control
#define NUM_C 4

int x = 0;
int y = 0;
int z = 0;
//Set up inputs and outputs
int pot_value[4] = {0, 0, 0, 0};
int pot_pins = {A0, A1, A2, A3};
int out_pins = {3, 5, 6, 9};
int pressed = 0;
int screen_out = 11;

//Set up constants
#define SCREEN_RES 250
#define DELAY_TIME 100
//Set up screen
#define YP A4  // must be an analog pin, use "An" notation!
#define XM A5  // must be an analog pin, use "An" notation!
#define YM 8   // can be a digital pin
#define XP 10  // can be a digital pin
TouchScreen ts = TouchScreen(XP, YP, XM, YM, SCREEN_RES);

void setup() {
	//Set up outputs
	for(int i = 0; i < NUM_C; i++)
	{
		pinMode(out_pins[i], OUTPUT);
	}
	pinMode(out_pins[i], OUTPUT);
	//Set up debugging info
	Serial.begin(9600);
	

}

void loop() {
	int loop_count = 0;
	
	// a point object holds x y and z coordinates
  	TSPoint p = ts.getPoint();
  
  	// Read in touch screen if you are touching it
  	if (p.z > ts.pressureThreshhold && pressed == 0) {
		//Store x and y values
		x = p.x;
		y = p.y;
		pressed = 1;
		Serial.print("Getting Touch Input")
		Serial.print("X = "); Serial.print(p.x);
     	Serial.print("\tY = "); Serial.print(p.y);
     	Serial.print("\tPressure = "); Serial.println(p.z);
  	}

	while(pressed == 1)
	{
		//Read in analog values from potentiometers
		for(int i = 0; i < NUM_POTS; i++)
		{
			pot_value[i] = analogRead(pots_pin[i]);
		}
		
		//Modify and scale the values if needed
		for(int i = 0; i < NUM_POTS; i++)
		{
			pot_value[i] = map(pot_value[i], 0, 1023, 0, 255);
		}
		
		//Write values out to PWM pins
		for(int i = 0; i < NUM_C; i++)
		{
			analogWrite(out_pins[i], pot_value[i]);
		}
		//Process screen data
		z = x + y;
		z = map(z, 0, 1023, 0, 255);
		analogWrite(screen_out, z);
		
		//If 100 ms has passed, read touch screen input
		delay(1);
		loop_count++;
		if(loop_count >= DELAY_TIME)
		{
			pressed = 0;
			loop_count = 0;
		}
	}


}
