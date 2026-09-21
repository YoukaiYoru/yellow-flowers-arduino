# 🌼 Feliz primavera con Arduino UNO

Proyecto con texto desplazable en cuatro matrices LED 8×8 con controlador MAX7219 y una flor formada por siete LEDs de pétalos y un LED central.

## Materiales

- Arduino UNO o compatible
- 4 módulos de matriz 8×8 MAX7219 conectados en cadena
- 8 LEDs
- 8 resistencias de 220 Ω (una por LED)
- Cables y protoboard

## Conexiones

### Cadena MAX7219

| MAX7219 | Arduino UNO |
|---|---:|
| VCC | 5V |
| GND | GND |
| DIN | D11 |
| CS/LOAD | D10 |
| CLK | D13 |

Conecta `DOUT` de cada módulo al `DIN` del siguiente.

### Flor

Conecta el ánodo de cada LED a un pin mediante una resistencia de 220 Ω y todos los cátodos a GND:

- Pétalos: D2, D3, D4, D5, D6, D7 y D8
- Centro: D9

## Funcionamiento

El texto `FELIZ PRIMAVERA` se desplaza continuamente por las cuatro matrices. La flor mantiene encendido el centro y anima dos pétalos consecutivos.

Abre `sketch/sketch.ino` en Arduino IDE, selecciona **Arduino Uno** y carga el programa.

Si el texto aparece invertido, gira físicamente la cadena de matrices 180° o invierte la orientación de los módulos en el montaje.



