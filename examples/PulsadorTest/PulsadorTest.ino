/*
 * PushButton Test
 * Prueba un pulsador
 */

#include <Robotec.h>

// Constantes
const int BOTON_PIN = 2;
const int START_TIME = 2000;

// Pin, Modo de conexion: PULL_UP (resistencia externa), 
// PULL_UP_INTERNAL (resistencia interna), PULL_DOWN (resistencia externa)
Button boton(BOTON_PIN, PULL_UP_INTERNAL);

// Definicion de LED auxiliar
Led led(LED_BUILTIN);

void setup() {
  
  Serial.begin(9600);

  // Enciende un LED hasta que transcurra un tiempo desde pulsador el boton
  // Luego lo apaga 
  led.on();
  //boton.pushStart(START_TIME);
  led.off();
}

void loop() {

  // Lee el estado del pulsador
  bool statusButton = boton.push();
  if (statusButton) Serial.println(statusButton);
  
}