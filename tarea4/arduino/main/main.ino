
/*
 * Main Functions
 */

void setup() {
	setupRelay();
	setupCommunication();
}

void loop() {
	communicate();
	delay(500);
}

/*
 * Communication
 */

void setupCommunication() {
	Serial.begin(9600);
}

void communicate() {
	Serial.print("Distancia: ");
	Serial.println(isNear());

	Serial.print("Humedad: ");
	Serial.println(getHumidity());
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

boolean isNear() {
	return getUltrasonicDistance() < 10;
}


/*
 * Relay
 */

int relayPin = 11;

void setupRelay() {
	pinMode(relayPin, OUTPUT);
}

void relayOn() {
	digitalWrite(relayPin, HIGH);
}

void relayOff() {
	digitalWrite(relayPin, LOW);
}














