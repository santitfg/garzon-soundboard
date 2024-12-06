#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

// Configura los pines de soft serial (elige pines GPIO disponibles)
SoftwareSerial mySoftwareSerial(21,20); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

void setup() {
  Serial.begin(115200);
  
  // Inicializa el soft serial a 9600 baudios
  mySoftwareSerial.begin(9600);
  
  Serial.println(F("Inicializando DFPlayer ... (Puede tardar 3~5 segundos)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println(F("No se puede inicializar:"));
    Serial.println(F("1. Revisa las conexiones"));
    Serial.println(F("2. Inserta una tarjeta SD"));
    while(true);
  }
  
  Serial.println(F("DFPlayer Mini inicializado"));
  
  // Configura el volumen (0-30)
  myDFPlayer.volume(15);
}

void loop() {
  // Ejemplo: reproducir la primera pista
  myDFPlayer.play(1);
  delay(30000); // Espera 3 segundos
  
  // Puedes agregar más funciones como:
  // myDFPlayer.pause();
  // myDFPlayer.next();
  // myDFPlayer.previous();
}
