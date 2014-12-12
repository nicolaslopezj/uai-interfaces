/**
 * Pines
 */

int pinLed1Verde = A0;
int pinLed1Rojo = A1;
int pinLed2Verde = A2;
int pinLed2Rojo = A3;

int pinPir1 = 12;
int pinPir2 = 13;

int pinAxis1 = 8;
int pinAxis2 = 10;

int pinUltrasonic1DerechaEcho = 4;
int pinUltrasonic1DerechaTrig = 5;
int pinUltrasonic1IzquierdaEcho = 6;
int pinUltrasonic1IzquierdaTrig = 7;
int pinUltrasonic2DerechaEcho = A5;
int pinUltrasonic2DerechaTrig = A4;
int pinUltrasonic2IzquierdaEcho = 2;
int pinUltrasonic2IzquierdaTrig = 3;

/**
 * Communication
 */

void setupCommunication() {
	Serial.begin(9600);
}

void readSerial() {
	if (Serial.available() > 0) {
		String result = Serial.readString();

		if (result.equals("0")) {
			showGameResult(0);
		} else if (result.equals("1")) {
			showGameResult(1);
		} else if (result.equals("2")) {
			showGameResult(2);
		} else if (result.equals("3")) {
			showGameResult(3);
		}

		delay(1000);
		showGameResult(4);
	}
}

void communicate() {
	Serial.print(getAxis1Val());
	Serial.print(",");
	Serial.print(getAxis2Val());
	Serial.print(",");
	Serial.print(isPir1Active());
	Serial.print(",");
	Serial.print(isPir2Active());
	Serial.print(",");
	Serial.print(isUltrasonicOn(11));
	Serial.print(",");
	Serial.print(isUltrasonicOn(12));
	Serial.print(",");
	Serial.print(isUltrasonicOn(21));
	Serial.print(",");
	Serial.print(isUltrasonicOn(22));
	Serial.println(",");

	readSerial();
}

/**
 * Leds
 */

void initLeds() {
	pinMode(pinLed1Verde, OUTPUT); // Player 1 Verde
	pinMode(pinLed1Rojo, OUTPUT); // Player 1 Rojo
    pinMode(pinLed2Verde, OUTPUT); // Player 2 Verde
	pinMode(pinLed2Rojo, OUTPUT); // Player 2 Rojo
}

void showGameResult(int gameResult) {
	if (gameResult == 0) {
		digitalWrite(pinLed1Verde, LOW);
		digitalWrite(pinLed1Rojo, HIGH);
		digitalWrite(pinLed2Verde, LOW);
		digitalWrite(pinLed2Rojo, HIGH);
	}
	if (gameResult == 1) {
		digitalWrite(pinLed1Verde, HIGH);
		digitalWrite(pinLed1Rojo, LOW);
		digitalWrite(pinLed2Verde, LOW);
		digitalWrite(pinLed2Rojo, HIGH);
	}
	if (gameResult == 2) {
		digitalWrite(pinLed1Verde, LOW);
		digitalWrite(pinLed1Rojo, HIGH);
		digitalWrite(pinLed2Verde, HIGH);
		digitalWrite(pinLed2Rojo, LOW);
	}
	if (gameResult == 3) {
		digitalWrite(pinLed1Verde, HIGH);
		digitalWrite(pinLed1Rojo, LOW);
		digitalWrite(pinLed2Verde, HIGH);
		digitalWrite(pinLed2Rojo, LOW);
	}
	if (gameResult == 4) {
		digitalWrite(pinLed1Verde, LOW);
		digitalWrite(pinLed1Rojo, LOW);
		digitalWrite(pinLed2Verde, LOW);
		digitalWrite(pinLed2Rojo, LOW);
	}
}

/**
 * Sensor PIR
 */

int waitingTime = 15;

void initPir() {
	pinMode(pinPir1, INPUT);
	digitalWrite(pinPir1, LOW);
    delay(waitingTime * 1000);
	pinMode(pinPir2, INPUT);
	digitalWrite(pinPir2, LOW);
	delay(waitingTime * 1000);
}

boolean isPir1Active() {
	return digitalRead(pinPir1) == HIGH;
}

boolean isPir2Active() {
	return digitalRead(pinPir2) == HIGH;
}

/**
 * Axis
 */

int getAxis1Val() {
	return digitalRead(pinAxis1);
}

int getAxis2Val() {
	return digitalRead(pinAxis2);
}



/**
 * Ultrasonic
 */

#include "Ultrasonic.h"

Ultrasonic ultrasonic11(pinUltrasonic1DerechaTrig, pinUltrasonic1DerechaEcho); // Player 1 Derecha
Ultrasonic ultrasonic12(pinUltrasonic1IzquierdaTrig, pinUltrasonic1IzquierdaEcho); // Player 1 Izq
Ultrasonic ultrasonic21(pinUltrasonic2DerechaTrig, pinUltrasonic2DerechaEcho); // Player 2 Derecha
Ultrasonic ultrasonic22(pinUltrasonic2IzquierdaTrig, pinUltrasonic2IzquierdaEcho); // Player 2 Izq

boolean isUltrasonicOn(int id) {
	if (id == 11) {
		return ultrasonic11.Ranging(CM) < 20;
	}
	if (id == 12) {
		return ultrasonic12.Ranging(CM) < 20;
	}
	if (id == 21) {
		return ultrasonic21.Ranging(CM) < 20;
	}
	if (id == 22) {
		return ultrasonic22.Ranging(CM) < 20;
	}
}

int getDistance(int id) {
    if (id == 11) {
		return ultrasonic11.Ranging(CM);
	}
	if (id == 12) {
		return ultrasonic12.Ranging(CM);
	}
	if (id == 21) {
		return ultrasonic21.Ranging(CM);
	}
	if (id == 22) {
		return ultrasonic22.Ranging(CM);
	}
}

/**
 * Main
 */

void setup() {
	initLeds();
        //initPir();
 	setupCommunication();
}

void loop() {
	communicate();
	delay(40);
}
