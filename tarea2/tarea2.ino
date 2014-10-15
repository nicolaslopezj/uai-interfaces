
int pinBoton = 7;
int pinFlexion = A0;
int pinIrLed = 12;
int pinIrSensor = 6;
int irSignal(int sP, int lP);

void setup() {
  Serial.begin(9600);
  pinMode(pinBoton, INPUT_PULLUP);
  pinMode(pinIrSensor, INPUT);
  pinMode(pinIrLed, OUTPUT);
}

void loop() {
  delay(5);
  communicate();
}

boolean isBotonOn() {
  int botonVal = digitalRead(pinBoton);
  return botonVal == 0;
}

boolean isFlexionOn() {
  int flexionVal = analogRead(pinFlexion);
  return flexionVal < 410;
}

boolean isIrOn() {
  int irVal = irSignal(pinIrSensor, pinIrLed);
  return irVal == 0;
}

void communicate() {
  Serial.print(isBotonOn());
  Serial.print(",");
  Serial.print(isFlexionOn());
  Serial.print(",");
  Serial.print(isIrOn());
  Serial.println("");
}

int irSignal (int sP, int lP) {
  int periodo = 13;
  int ciclos = 38; 
  
  for (int i = 0; i < ciclos; i++) {
    digitalWrite(lP, HIGH);
    delayMicroseconds(periodo);
    digitalWrite(lP, LOW);
    delayMicroseconds(periodo);
  }
  
  return digitalRead(sP);
}
