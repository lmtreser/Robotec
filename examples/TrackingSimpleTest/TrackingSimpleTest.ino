/*
 * Tracking Simple Test
 * Imprime en pantalla el estado del sensor tracking simple
 */

#include <Robotec.h>

// Constantes pines
const int OUT_PIN = 4;

// Otras constantes
const int DELAY_TIME = 1000;

// Pin OUT, linea negra = LOW (por defecto)
Tracking sensorLinea(OUT_PIN);
// Pin OUT, linea negra = HIGH
// Tracking sensorLinea(outPin, true);

int follow;

void setup() {

  Serial.begin(9600);
}

void loop() {

  follow = sensorLinea.read(); // devuelve HIGH si detecta la linea

  if (follow == HIGH) {
    Serial.println("Linea detectada :)");
  } else {
    Serial.println("Fuera de la linea :(");
  }

  delay(DELAY_TIME);
}