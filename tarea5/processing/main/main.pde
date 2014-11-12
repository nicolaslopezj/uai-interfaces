import processing.serial.*;

Serial puerto;
int points = 0;
boolean lastColor;
boolean isBlack;

void setup() {
 
  size(500, 500);
  
  println(Serial.list());
  print("Connecting to: ");
  println(Serial.list()[3]);
  puerto = new Serial(this, Serial.list()[2], 9600);
  puerto.bufferUntil('\n');
  
}

void serialEvent(Serial puerto)
{
  String mensaje = puerto.readStringUntil('\n');
  if (mensaje != null) {
    try {
      String[] datos = mensaje.split(";");
      isBlack = int(datos[2]) > 200;
      print("Mensaje: ");
      println(mensaje);
      print("Color: ");
      print(isBlack ? "negro" : "blanco");
      print(" Valor: ");
      println(datos[2]);
    } catch (Exception e) {
      
    }
  }
}

void draw() {
  textAlign(CENTER, CENTER);
  
  if (!lastColor && isBlack) {
    points++;
  }
  
  lastColor = isBlack;
  int background = isBlack ? 0 : 255;
  background(background);
  
  textSize(50);
  fill(122);
  text(points, 250, 100);
  
}
