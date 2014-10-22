#include <Ultrasonic.h>
#include <CapacitiveSensor.h>

CapacitiveSensor cs_4_2 = CapacitiveSensor(4, 2);
Ultrasonic ultrasonic(13, 12);

void setup() {
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);
  Serial.begin(9600);
}

void loop() {
  long capacitive = cs_4_2.capacitiveSensor(30);
  int distance = ultrasonic.Ranging(CM);
  
  Serial.print(capacitive);
  Serial.print(",");
  Serial.print(distance);
  Serial.println(",");
  delay(50);
}
