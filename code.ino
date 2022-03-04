#define POT1 0
#define POT2 1
#define POT3 2
#define POT4 3
#define NUM_POTS 4
//analogRead('a'+antenna)
#define C1 3
#define C2 5
#define C3 6
#define C4 9
#define NUM_C 4 
//analogWrite(motor, 0);

void setup() {
	pixels.begin(); 
	pixels.setBrightness(50); 
	pixels.clear();
	
	pinMode(photogate,INPUT); 
	pinMode(motor,OUTPUT); 
	
	unsigned long startTime = millis();
	analogWrite(motor, motorSpeed);
	
  do {	
    if(digitalRead(photogate) == 1 && rotationSpeed == 0)
    {
      unsigned long stopMillis = millis();
      rotationSpeed = stopMillis - startTime;
     }   
  } while(digitalRead(photogate) == 0 && rotationSpeed == 0);
	
	analogWrite(motor, 0);

	//indicate that it has calibrated
	for(int i = 0; i < NUMPIXELS; i++)
	{
		pixels.setPixelColor(0, pixels.Color(0,63,0));
		pixels.show();
	}
	delay(500);
	pixels.clear();
	
	
	numRead = floor(rotationSpeed/10);
	analogWrite(motor, motorSpeed);
	
}

void loop() {
	
	for(int i = 0; i< NUMPIXELS; i++)
	{
    int sum = 0; 
    int average = 0;
    int color = 0;
    
		for(int j = 0; j < numRead; j++)
		{
		  sum = sum + analogRead('a'+antenna);
		  delay(10);
		}

    average = floor(sum/numRead);

    color = map(average, 0, 1023, 0, 255);
    
	pixels.setPixelColor(i, pixels.Color(color, color, color));
    pixels.show();
	}
}