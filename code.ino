/*
	UIUC ECE 110 Honors Lab Spring 2022
	Group 30
	Members: Akash Chandra & Asaiah Rock
	The touch screen code can be found here: https://github.com/adafruit/Adafruit_TouchScreen
	We using the same method to read the screen as https://github.com/adafruit/Adafruit_TouchScreen/blob/master/examples/touchscreendemo/touchscreendemo.ino
*/

#include <stdint.h>
#include "TouchScreen.h"

int a, b, c, x, y, f;

int screen_out = 11;

//Set up constants
#define SCREEN_RES 250
//Set up screen
#define YP A4  // must be an analog pin, use "An" notation!
#define XM A5  // must be an analog pin, use "An" notation!
#define YM 8   // can be a digital pin
#define XP 10  // can be a digital pin
TouchScreen ts = TouchScreen(XP, YP, XM, YM, SCREEN_RES);

void setup() {
	pinMode(3, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(screen_out, OUTPUT);
	//Set up debugging info
	Serial.begin(9600);
	

}

void loop() {
	// a point object holds x y and z coordinates
  	TSPoint p = ts.getPoint();
  
  	// Read in touch screen if you are touching it
  	if (p.z > ts.pressureThreshhold) {
		//Store x and y values
		x = p.x;
		y = p.y;
		Serial.print("\nGetting Touch Input");
		Serial.print("\tX = "); Serial.print(p.x);
     	Serial.print("\tY = "); Serial.print(p.y);
     	Serial.print("\tPressure = "); Serial.println(p.z);
		Serial.print("\n")
  	}

	a = analogRead(A0);
    Serial.print(a); Serial.print(" a\n");  
    a = map(a, 0, 1023, 0, 200);
	analogWrite(3, a);
	
	b = analogRead(A1);
    Serial.print(b); Serial.print(" b\n");  
    b = map(b, 0, 1023, 0, 200);
	analogWrite(5, b);
	
	c = analogRead(A2);
    Serial.print(c); Serial.print(" c\n");  
    c = map(c, 0, 1023, 0, 200);
	analogWrite(6, c);
	
	f = x + y;
    Serial.print(f); Serial.print(" f\n");  
    f = map(f, 0, 4000, 0, 200);
	analogWrite(screen_out, f);


}
