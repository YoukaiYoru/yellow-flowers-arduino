// Arduino UNO Q: mensaje de primavera y flor usando solamente
// la matriz LED azul integrada de 8 x 13.

#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

Arduino_LED_Matrix matrix;

// Flor de 8 filas x 13 columnas, en formato fila por fila.
const uint8_t flower[104] = {
  0,0,0,0,0,1,0,1,0,0,0,0,0,
  0,0,0,0,1,1,1,1,1,0,0,0,0,
  0,0,0,1,1,1,1,1,1,1,0,0,0,
  0,0,1,1,1,1,1,1,1,1,1,0,0,
  0,0,0,1,1,1,1,1,1,1,0,0,0,
  0,0,0,0,1,1,1,1,1,0,0,0,0,
  0,0,0,0,0,0,1,0,0,0,0,0,0,
  0,0,0,0,0,0,1,0,0,0,0,0,0
};

void setup() {
  matrix.begin();
  matrix.setGrayscaleBits(1);
  matrix.textFont(Font_5x7);
  matrix.textScrollSpeed(90);
  matrix.clear();
}

void loop() {
  // El mensaje avanza automáticamente por la matriz integrada.
  matrix.beginText(0, 0, 127, 0, 0);
  matrix.print(" FELIZ PRIMAVERA ");
  matrix.endText(SCROLL_LEFT);

  delay(500);

  // Después aparece la flor durante unos segundos.
  matrix.draw(flower);
  delay(1800);
  matrix.clear();
}
