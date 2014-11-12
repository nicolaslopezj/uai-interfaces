/*
 * Encoder
 */

int encoderPin1 = 2;
int encoderPin2 = 3;

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;

int lastMSB = 0;
int lastLSB = 0;

void setupEncoder() {
	pinMode(encoderPin1, INPUT); 
	pinMode(encoderPin2, INPUT);

	digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
	digitalWrite(encoderPin2, HIGH); //turn pullup resistor on

	//call updateEncoder() when any high/low changed seen
	//on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
	attachInterrupt(0, updateEncoder, CHANGE); 
	attachInterrupt(1, updateEncoder, CHANGE);

}

void updateEncoder() {
	int MSB = digitalRead(encoderPin1); //MSB = most significant bit
	int LSB = digitalRead(encoderPin2); //LSB = least significant bit


	int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
	int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

	
	if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011)
		 encoderValue ++;
	if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) 
		 encoderValue --;

	lastEncoded = encoded; //store this value for next time
}

/*
 * Motor
 */

int speedPinL = 11;
int speedPinR = 9;
int motor1APin = 6;
int motor2APin = 7;
int motor3APin = 4;
int motor4APin = 5;
int speedValue = 250;

void setupMotor() {

	pinMode(speedPinR, OUTPUT);
	pinMode(speedPinL, OUTPUT);

	pinMode(motor1APin, OUTPUT);
	pinMode(motor2APin, OUTPUT);

	pinMode(motor3APin, OUTPUT);
	pinMode(motor4APin, OUTPUT);	
}

void controlMotor() {
	int speed1 = 0;
	int speed2 = 0;

	if (encoderValue > 0) {
		speed1 = encoderValue * 10;
		speed2 = encoderValue * 7;
	} else if (encoderValue < 0) {
		speed1 = encoderValue * -7;
		speed2 = encoderValue * -10;
	}

	moveMotor(speed1, speed2);
	Serial.print(speed1);
	Serial.print(" : ");
	Serial.println(speed2);
}

void moveMotor(int speed1, int speed2) {
	digitalWrite(motor1APin, LOW);
	digitalWrite(motor2APin, HIGH);
	analogWrite(speedPinR, speed1);

	digitalWrite(motor3APin, LOW);
	digitalWrite(motor4APin, HIGH);
	analogWrite(speedPinL, speed2);
}

/*
 * QD Sensor
 */

#define QRE1113_Pin 5
int qdValue = 0;

void readQD() {
	//Returns value from the QRE1113 
	//Lower numbers mean more refleacive
	//More than 3000 means nothing was reflected.
	pinMode( QRE1113_Pin, OUTPUT );
	digitalWrite( QRE1113_Pin, HIGH );  
	delayMicroseconds(10);
	pinMode( QRE1113_Pin, INPUT );

	long time = micros();

	//time how long the input is HIGH, but quit after 3ms as nothing happens after that
	while (digitalRead(QRE1113_Pin) == HIGH && micros() - time < 3000); 
	int diff = micros() - time;

	qdValue = diff;
}

/*
 * Communication
 */

void setupCommunication() {
	Serial.begin (9600);
}

void communicate() {
	Serial.print(encoderValue);
	Serial.print(";");
	Serial.print(qdValue > 150);
	Serial.print(";");
	Serial.print(qdValue);
	Serial.println(";");
}

/*
 * Main
 */

void setup() {
	setupCommunication();
	setupEncoder();
	setupMotor();
}

void loop() {
	readQD();
	updateEncoder();
	communicate();
	controlMotor();
	delay(50); 
}


