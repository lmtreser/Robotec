/*
 * PushButton Test
 * Prueba un pulsador
 */

#include <Robotec.h>

// Constantes con pin
const int BOTON_PIN = 2;

// Pin, Modo de conexion: PULL_UP (resistencia externa), 
// PULL_UP_INTERNAL (resistencia interna), PULL_DOWN (resistencia externa)
Button boton(BOTON_PIN, PULL_UP_INTERNAL);

void setup() {
  
  Serial.begin(9600);
}

void loop() {

  // Lee el estado del pulsador
  bool statusButton = boton.push();
  if (statusButton) Serial.println(statusButton);
  
}