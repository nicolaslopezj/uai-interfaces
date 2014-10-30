import controlP5.*;
import processing.serial.*;

Serial puerto;
ControlP5 controlP5;

float distanceControl = 0;
int distanceVal = 20;
int humidityVal = 40;

void setup() {
  size(600, 600);
  
  println(Serial.list());
  puerto = new Serial(this, Serial.list()[3], 9600);
  puerto.bufferUntil('\n');
  
  controlP5 = new ControlP5(this);
  controlP5.addSlider("SET TIME", 2, 21, 50, 100, 40, 400);
}

void serialEvent(Serial puerto)
{
  String mensaje = puerto.readStringUntil('\n');
  if (mensaje != null) {
    try {
      String[] datos = mensaje.split(",");
      distanceVal = int(datos[0]);
      humidityVal = int(datos[1]);
      print("Humedad: ");
      println(humidityVal);
      //println(datos[3]);
    } catch (Exception e) {
      
    }
  }
}

void controlEvent(ControlEvent theEvent) {  
  if(theEvent.isController()) { 
    distanceControl = theEvent.controller().value();
  }  
}


void draw() {
  background(0);
  
  //println(distanceControl);
  //println(distanceVal);
  
  drawBaseRectangles();
  drawStatusRectangles();
  drawOnCircle();
  
  if (16 > distanceVal) {
      puerto.write("1\n");
      delay(int(distanceControl));
  } else {
      puerto.write("0\n");
  }
}

void drawBaseRectangles() {
  fill(255, 255, 255);
  rect(150, 100, 40, 400);
  rect(250, 100, 40, 400);
}

void drawStatusRectangles() {
  float mappedDistance = map(distanceVal, 2, 21, 400, 0);
  float mappedHumidity = map(humidityVal, 30, 50, 400, 0);
  
  fill(0, 255, 255);
  rect(150, 100 + mappedDistance, 40, 400 - mappedDistance);
  rect(250, 100 + mappedHumidity, 40, 400 - mappedHumidity);
}

void drawOnCircle() {
  if (distanceControl > distanceVal) {
    // ON
    fill(0, 255, 0);
    ellipse(400, 250, 100, 100);
  } else {
    // OFF
    fill(255, 0, 0);
    ellipse(400, 250, 100, 100);
  }
}
