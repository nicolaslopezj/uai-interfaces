
class BooleanIndicatorCircle {
  
  float radio = 20;
  float x = 0, y = 0;
  
  BooleanIndicatorCircle(float _x, float _y, float _radio) {
    x = _x;
    y = _y;
    radio = _radio;
  }
  
  void setBoolean(boolean bool) {
    
    noStroke();
    if (bool) {
      fill(0, 255, 0);
    } else {
      fill(255, 0, 0);
    }
    
    ellipse(x, y, radio, radio);
    
  }
  
}
