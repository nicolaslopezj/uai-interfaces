import themidibus.*;
import processing.serial.*;

Serial puerto; 

int channel = 0;
int velocity = 50;
MidiBus myBus;

boolean botonOn;
int distance;

void setup() {
  
  size(600, 600);
  MidiBus.list();
  myBus = new MidiBus(this, -1, 0);
  
  println(Serial.list());
  puerto = new Serial(this, Serial.list()[3], 9600);
  puerto.bufferUntil('\n');
  
}

void draw() {
  textAlign(CENTER, CENTER);
  
  setColor();
  if (botonOn && distance <= 40) {
    int pitch = ceil(map(distance, 5, 40, 90, 50));
    println(pitch);
    myBus.sendNoteOn(channel, pitch, velocity);
  }
  
  fill(255, 255, 255);
  textSize(20);
  text(distance, 300, 20);
}

void setColor() {

  int r = 125;
  int g = ceil(map(distance, 0, 51, 50, 205));
  int b = 125;

  background(r,g,b);
}

void serialEvent(Serial puerto)
{
  String mensaje = puerto.readStringUntil('\n');
  if (mensaje != null) {
    try {
      String[] datos = mensaje.split(",");
      botonOn = datos[0].equals("1");
      println(botonOn);
      distance = int(datos[1]);
    } catch (Exception e) {
      
    }
  }
}
