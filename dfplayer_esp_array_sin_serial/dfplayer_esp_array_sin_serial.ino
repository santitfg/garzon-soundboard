#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>


// Configuración de pines
const int colPins[4] = {0, 1, 2, 3};  // C1-C4
const int rowPins[4] = {5, 6, 7, 8};   // R1-R4

SoftwareSerial mySoftwareSerial(21, 20); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
int buttonPressedA = 0;

void setup() {

  // Inicializar columnas como salidas
  for (int i = 0; i < 4; i++) {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH); // Desactivar columnas inicialmente
  }

  // Inicializar filas como entradas con pullup
  for (int i = 0; i < 4; i++) {
    pinMode(rowPins[i], INPUT_PULLUP);
  }

  // Inicializar DFPlayer
  mySoftwareSerial.begin(9600);
  myDFPlayer.begin(mySoftwareSerial);

  myDFPlayer.volume(30);//30 db max
}

int scanButtons() {
  for (int col = 0; col < 4; col++) {
    // Activar solo una columna
    for (int c = 0; c < 4; c++) {
      digitalWrite(colPins[c], c == col ? LOW : HIGH);
    }

    // Verificar filas
    for (int row = 0; row < 4; row++) {
      if (digitalRead(rowPins[row]) == LOW) {
        // Calcular número de botón
        return col * 4 + row + 1;
      }
    }
  }
  return -1; // Ningún botón presionado
}
void loop() {
  int buttonPressed = scanButtons();

  if (buttonPressed != -1 && buttonPressed != buttonPressedA) {

    // Reproducir pista de audio correspondiente al botón
    myDFPlayer.play(buttonPressed);

    // Debounce
    delay(50);

    // Esperar a que se suelte el botón
    // while(scanButtons() != -1);
  }
  // delay(50);
  buttonPressed = buttonPressedA;
}
