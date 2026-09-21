// Feliz primavera: texto desplazable en 4 matrices MAX7219
// y una flor animada con 7 petalos + 1 LED central.

const byte PIN_DIN = 11;
const byte PIN_CS  = 10;
const byte PIN_CLK = 13;
const byte NUM_MATRICES = 4;

const byte PETAL_FIRST_PIN = 2;
const byte PETAL_COUNT = 7;
const byte CENTER_PIN = 9;

const char MESSAGE[] = "FELIZ PRIMAVERA";
const byte MESSAGE_LENGTH = sizeof(MESSAGE) - 1;
const byte MATRIX_WIDTH = NUM_MATRICES * 8;
const byte LETTER_WIDTH = 6;
const int TEXT_WIDTH = MESSAGE_LENGTH * LETTER_WIDTH;
const int SCROLL_LIMIT = TEXT_WIDTH + MATRIX_WIDTH;

int scrollPosition = -MATRIX_WIDTH;
unsigned long lastScroll = 0;
unsigned long lastFlower = 0;
byte flowerStep = 0;

void sendCommand(byte address, byte value) {
  digitalWrite(PIN_CS, LOW);
  for (int module = NUM_MATRICES - 1; module >= 0; module--) {
    shiftOut(PIN_DIN, PIN_CLK, MSBFIRST, address);
    shiftOut(PIN_DIN, PIN_CLK, MSBFIRST, value);
  }
  digitalWrite(PIN_CS, HIGH);
}

void setupMatrix() {
  pinMode(PIN_DIN, OUTPUT);
  pinMode(PIN_CS, OUTPUT);
  pinMode(PIN_CLK, OUTPUT);

  sendCommand(0x0F, 0x00);
  sendCommand(0x0C, 0x01);
  sendCommand(0x0B, 0x07);
  sendCommand(0x09, 0x00);
  sendCommand(0x0A, 0x03);

  for (byte row = 1; row <= 8; row++) {
    sendCommand(row, 0x00);
  }
}

// Cada letra es una fuente de 5x7. El bit 0 es la fila superior.
byte glyph(char letter, byte column) {
  if (column >= 5) return 0;

  switch (letter) {
    case 'F': { const byte g[5] = {0x7F, 0x09, 0x09, 0x09, 0x01}; return g[column]; }
    case 'E': { const byte g[5] = {0x7F, 0x49, 0x49, 0x49, 0x41}; return g[column]; }
    case 'L': { const byte g[5] = {0x7F, 0x40, 0x40, 0x40, 0x40}; return g[column]; }
    case 'I': { const byte g[5] = {0x41, 0x41, 0x7F, 0x41, 0x41}; return g[column]; }
    case 'Z': { const byte g[5] = {0x61, 0x51, 0x49, 0x45, 0x43}; return g[column]; }
    case 'P': { const byte g[5] = {0x7F, 0x09, 0x09, 0x09, 0x06}; return g[column]; }
    case 'R': { const byte g[5] = {0x7F, 0x09, 0x19, 0x29, 0x46}; return g[column]; }
    case 'M': { const byte g[5] = {0x7F, 0x02, 0x04, 0x02, 0x7F}; return g[column]; }
    case 'A': { const byte g[5] = {0x7E, 0x09, 0x09, 0x09, 0x7E}; return g[column]; }
    case 'V': { const byte g[5] = {0x1F, 0x20, 0x40, 0x20, 0x1F}; return g[column]; }
    default: return 0;
  }
}

byte textColumn(int x) {
  if (x < 0 || x >= TEXT_WIDTH) return 0;
  byte letter = x / LETTER_WIDTH;
  byte column = x % LETTER_WIDTH;
  return glyph(MESSAGE[letter], column);
}

void drawText() {
  for (byte row = 0; row < 8; row++) {
    byte matrixData[NUM_MATRICES] = {0, 0, 0, 0};

    for (byte screenColumn = 0; screenColumn < MATRIX_WIDTH; screenColumn++) {
      int sourceColumn = scrollPosition + screenColumn;
      byte columnBits = textColumn(sourceColumn);
      if (columnBits & (1 << row)) {
        byte matrix = screenColumn / 8;
        byte column = screenColumn % 8;
        matrixData[matrix] |= (1 << (7 - column));
      }
    }

    digitalWrite(PIN_CS, LOW);
    for (int matrix = NUM_MATRICES - 1; matrix >= 0; matrix--) {
      shiftOut(PIN_DIN, PIN_CLK, MSBFIRST, row + 1);
      shiftOut(PIN_DIN, PIN_CLK, MSBFIRST, matrixData[matrix]);
    }
    digitalWrite(PIN_CS, HIGH);
  }
}

void animateFlower() {
  for (byte petal = 0; petal < PETAL_COUNT; petal++) {
    digitalWrite(PETAL_FIRST_PIN + petal, LOW);
  }

  digitalWrite(PETAL_FIRST_PIN + flowerStep, HIGH);
  digitalWrite(PETAL_FIRST_PIN + ((flowerStep + 1) % PETAL_COUNT), HIGH);
  digitalWrite(CENTER_PIN, HIGH);
  flowerStep = (flowerStep + 1) % PETAL_COUNT;
}

void setup() {
  setupMatrix();
  for (byte pin = PETAL_FIRST_PIN; pin <= CENTER_PIN; pin++) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }
  animateFlower();
}

void loop() {
  unsigned long now = millis();

  if (now - lastScroll >= 90) {
    lastScroll = now;
    drawText();
    scrollPosition++;
    if (scrollPosition > SCROLL_LIMIT) scrollPosition = -MATRIX_WIDTH;
  }

  if (now - lastFlower >= 140) {
    lastFlower = now;
    animateFlower();
  }
}
