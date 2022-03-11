#define NUM_POTS 4
//analogRead('a'+antenna)

#define NUM_C 4 
//analogWrite(motor, 0);

int pots[4] = {0, 0, 0, 0};
int pot_pins = {A0, A1, A2, A3};
int out_pins = {3, 5, 6, 9};

void setup() {
	pinMode(C1, OUTPUT);
	pinMode(C2, OUTPUT);
	pinMode(C3, OUTPUT);
	pinMode(C4, OUTPUT);
}

void loop() {
	
	//Read in analog values
	for(int i = 0; i < NUM_POTS; i++)
	{
		pots[i] = analogRead(pots_pin[i]);
	}
	
	//Modify the values if needed
	for(int i = 0; i < NUM_POTS; i++)
	{
		pots[i] = map(pots[i], 0, 1023, 0, 255);
	}
	
	//Write values out to PWM pins
	for(int i = 0; i < NUM_C; i++)
	{
		analogWrite(out_pins[i], pots[i]);
	}
}