
class ClosingCircle {
  
  float fullRadio = 20;
  float minRadio = 0;
  float currentRadio = 0;
  float x = 0, y = 0;
  int time;
  int initialTime;
  
  ClosingCircle(float _x, float _y, float _fullRadio, float _minRadio, int _time) {
    x = _x;
    y = _y;
    fullRadio = _fullRadio;
    currentRadio = _fullRadio;
    minRadio = _minRadio;
    time = _time;
    initialTime = millis();
  }
  
  boolean isReady() {
    if (getTimeLeft() < 0) {
      return true;
    }
    
    return false;
  }
  
  int getTimeLeft() {
    return time - (millis() - initialTime);
  }
  
  void run() {
    shrink();
    show();
  }
  
  void shrink() {
    float porcentaje = 100 * getTimeLeft() / time;
    float diff = (fullRadio - minRadio);
    currentRadio = minRadio + (diff * porcentaje * 0.01);
  }
  
  void show() {
    noStroke();
    fill(0, 0, 255);
    ellipse(x, y, currentRadio, currentRadio);
  }
  
  
  
}
