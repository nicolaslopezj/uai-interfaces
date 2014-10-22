#include <CapacitiveSensor.h>
#include <Ultrasonic.h>


CapacitiveSensor cs_4_2 = CapacitiveSensor(4, 2);
Ultrasonic ultrasonic(13, 12);

void setup() {
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  boolean capacitive = cs_4_2.capacitiveSensor(30) > 400;
  int distance = ultrasonic.Ranging(CM);
  
  Serial.print(capacitive);
  Serial.print(",");
  Serial.print(distance);
  Serial.println(",");
  
  ledLoop();
}

void ledLoop() {
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  delay(50);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  delay(50);
}
