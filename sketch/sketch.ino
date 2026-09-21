// Arduino UNO Q: mensaje de primavera y flor usando solamente
// la matriz LED azul integrada de 8 x 13.

#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

Arduino_LED_Matrix matrix;

// Flores de 8 filas x 13 columnas, en formato fila por fila.
// El centro queda separado de los petalos para que la figura se entienda mejor.
const uint8_t flowerA[104] = {
  0,0,0,0,0,1,1,1,0,0,0,0,0,
  0,0,0,1,1,1,1,1,1,1,0,0,0,
  0,0,1,1,1,0,1,0,1,1,1,0,0,
  0,1,1,0,0,1,1,1,0,0,1,1,0,
  0,0,1,1,1,1,1,1,1,1,1,0,0,
  0,0,0,0,1,1,1,1,1,0,0,0,0,
  0,0,0,0,0,0,1,0,0,0,0,0,0,
  0,0,0,1,1,0,1,0,0,1,1,0,0
};

const uint8_t flowerB[104] = {
  0,0,0,0,0,1,1,1,0,0,0,0,0,
  0,0,0,1,1,1,1,1,1,1,0,0,0,
  0,0,1,1,1,1,0,1,1,1,1,0,0,
  0,1,1,0,1,1,1,1,1,0,1,1,0,
  0,0,1,1,1,1,0,1,1,1,1,0,0,
  0,0,0,0,1,1,1,1,1,0,0,0,0,
  0,0,0,0,0,0,1,0,0,0,0,0,0,
  0,0,0,1,1,0,1,0,0,1,1,0,0
};

void setup() {
  matrix.begin();
  matrix.setGrayscaleBits(1);
  matrix.textFont(Font_5x7);
  matrix.textScrollSpeed(90);
  matrix.clear();
}

void loop() {
  matrix.beginText(0, 0, 127, 0, 0);
  matrix.print(" FELIZ PRIMAVERA ");
  matrix.endText(SCROLL_LEFT);

  delay(500);

  matrix.draw(flowerA);
  delay(600);
  matrix.draw(flowerB);
  delay(600);
  matrix.draw(flowerA);
  delay(600);
  matrix.clear();
}
