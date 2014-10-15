import processing.serial.*;

Serial puerto; 
boolean botonOn;
boolean sensorOn;
boolean irOn;
BooleanIndicatorCircle botonIndicatorCircle;
BooleanIndicatorCircle sensorIndicatorCircle;
BooleanIndicatorCircle irIndicatorCircle;
ClosingCircle closingCircle;
int currentChallenge;
int vidas = 3;
int rondas = 10;
int puntaje = 0;
int timeToAct = 1000;
int noActTime = 200;
int instrucciones = 100;
boolean waitingOut = false;

void setup() {
  
  size(600, 600);
  
  println(Serial.list());
  puerto = new Serial(this, Serial.list()[3], 9600);
  puerto.bufferUntil('\n');
  
  botonIndicatorCircle = new BooleanIndicatorCircle(300, 275, 75);
  sensorIndicatorCircle = new BooleanIndicatorCircle(500, 275, 75);
  irIndicatorCircle = new BooleanIndicatorCircle(100, 275, 75);
  
  newChallenge();
}

void draw() {
  textAlign(CENTER, CENTER);
  background(0);
  
  if (instrucciones > 0) {
    fill(255, 255, 255);
    
    textSize(50);
    text("Instrucciones", 300, 100);
    
    textSize(20);
    text("Este juego mide la velocidad de respuesta sensorial, y el tiempo que requiere para ejecutar una acción solicitada. Para ello debe presionar un botón, bloquear, o bien flexionar su dedo según el mensaje que sea desplegado en la interfaz gráfica. Solo tiene tres vidas, y en total solo hay 10 ciclos de pruebas generadas aleatoriamente.", 100, 80, 400, 500);
    
    textSize(20);
    text(instrucciones, 300, 550);
    
    instrucciones --;
    vidas = 4;
    rondas = 11;
  } else if (vidas == 0) {
    fill(255, 0, 0);
    
    textSize(50);
    text("Perdiste", 300, 250);
    
    textSize(30);
    text("Puntaje", 300, 310);
    textSize(42);
    text(puntaje, 300, 370);
  } else if (rondas == 0) {
    fill(0, 255, 0);
    
    textSize(50);
    text("Ganaste", 300, 250);
    
    textSize(30);
    text("Puntaje", 300, 310);
    textSize(42);
    text(puntaje, 300, 370);
  } else {
    fill(255, 255, 255);
    
    textSize(20);
    text("vidas", 100, 20);
    
    textSize(42);
    text(vidas, 100, 60);
    
    textSize(20);
    text("puntaje", 300, 20);
    
    textSize(42);
    text(puntaje, 300, 60);
    
    textSize(20);
    text("rondas", 500, 20);
    
    textSize(42);
    text(rondas, 500, 60);
    
    textSize(36);
    text("Boton", 300, 500);
    
    textSize(36);
    text("Dedo", 500, 500);
    
    textSize(36);
    text("Sensor", 100, 500);
    
    play();
    
    botonIndicatorCircle.setBoolean(botonOn);
    sensorIndicatorCircle.setBoolean(sensorOn);
    irIndicatorCircle.setBoolean(irOn);
  
  }
}

void play() {
  
  if (vidas <= 0) {
    return;
  }
  
  if (closingCircle.isReady()) {
    morir();
  } else {
    closingCircle.run();
  }
  
  checkTouch();
  
}

void checkTouch() {
  if (closingCircle.getTimeLeft() > timeToAct - noActTime) {
    return;
  }
  
  if (waitingOut) {
    return;
  }
  
  if (currentChallenge == 0) {
    if (botonOn && !sensorOn && !irOn) {
      ganar();
    } else if (sensorOn || irOn) {
      morir();
    }
  }
  if (currentChallenge == 1) {
    if (!botonOn && sensorOn && !irOn) {
      ganar();
    } else if (botonOn || irOn) {
      morir();
    }
  }
  if (currentChallenge == 2) {
    if (!botonOn && !sensorOn && irOn) {
      ganar();
    } else if (botonOn || sensorOn) {
      morir();
    }
  }
}

void ganar() {
  puntaje += getPuntaje();
  rondas --;
  waitingOut = true;
  newChallenge();
}

int getPuntaje() {
  return closingCircle.getTimeLeft();
}

void morir() {
  if (!waitingOut) {
    vidas --;
    rondas --;
  }
  waitingOut = true;
  newChallenge();
}

void newChallenge() {
  if (waitingOut) {
    if (botonOn || irOn || sensorOn) {
      return;
    }
  }
  waitingOut = false;
  
  currentChallenge = floor(random(0, 3));
  createClosingCircle();
}

void createClosingCircle() {
  float x = 0;
  float y = 0;
  if (currentChallenge == 0) {
    x = botonIndicatorCircle.x;
    y = botonIndicatorCircle.y;
  }
  if (currentChallenge == 1) {
    x = sensorIndicatorCircle.x;
    y = sensorIndicatorCircle.y;
  }
  if (currentChallenge == 2) {
    x = irIndicatorCircle.x;
    y = irIndicatorCircle.y;
  }
  closingCircle = new ClosingCircle(x, y, 200, 75, timeToAct);
}

void serialEvent(Serial puerto)
{
  String mensaje = puerto.readStringUntil('\n');
  if (mensaje != null) {
    try {
      String[] datos = mensaje.split(",");
      botonOn = datos[0].equals("1");
      sensorOn = datos[1].equals("1");
      irOn = datos[2].equals("1");
    } catch (Exception e) {
      
    }
  }
}
