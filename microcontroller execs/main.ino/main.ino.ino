
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6


Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(16, 16, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);



void setup() 
{
  matrix.begin();
  matrix.setBrightness(20);
  matrix.setTextColor( matrix.Color(255, 255, 255));
  matrix.setTextWrap(false);
}

void loop() {
  
}
