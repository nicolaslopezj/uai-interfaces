/*
 * Communication
 */

boolean motorState;
String message;

void setupCommunication() {
	Serial.begin(9600);
}

void communicate() {
	Serial.print(getUltrasonicDistance());
	Serial.print(",");
	Serial.print(getHumidity());
	Serial.print(",");
	Serial.print(motorState);
	Serial.print(",");
	Serial.print(message);
	Serial.println(",");
}

void readSerial() {
	if (Serial.available() > 0) {
		message = Serial.readStringUntil('\n');
		motorState = message.equals("on");
	}
}

/*
 * Humedad
 */

int pinHumidity = 4;

long getHumidity() {
	long result = 0;
	pinMode(pinHumidity, OUTPUT);
	digitalWrite(pinHumidity, HIGH);
	delay(1);
	pinMode(pinHumidity, INPUT);
	digitalWrite(pinHumidity, LOW);

	while(digitalRead(pinHumidity)) {
	    result ++;
	}

	return result;
}


/*
 * Ultrasonic
 */

#include "Ultrasonic.h"

Ultrasonic ultrasonic(13, 12);

int getUltrasonicDistance() {
	return ultrasonic.Ranging(CM);
}


/*
 * Relay
 */

int relayPin = 11;

void setupRelay() {
	pinMode(relayPin, OUTPUT);
}

void relaySet(boolean on) {

	if (on) {
		digitalWrite(relayPin, HIGH);
	} else {
		digitalWrite(relayPin, LOW);
	}
	
}

/*
 * Main Functions
 */

void setup() {
	setupRelay();
	setupCommunication();
}

void loop() {
	relaySet(motorState);
	readSerial();
	communicate();

	delay(200);
}








