/*
 * PushButton Test
 * Prueba un pulsador
 */

#include <Robotec.h>

// Constantes
const int BOTON_A_PIN = 2;
const int BOTON_B_PIN = 3;
const int START_TIME = 2000;

// Pin, Modo de conexion: PULL_UP (resistencia externa),
// PULL_UP_INTERNAL (resistencia interna), PULL_DOWN (resistencia externa)
Button botonPullUp(BOTON_A_PIN, PULL_UP_INTERNAL);
Button botonPullDown(BOTON_B_PIN, PULL_DOWN);

// Definicion de LED auxiliar
Led led(LED_BUILTIN);

void setup() {

  Serial.begin(9600);

  // Enciende un LED hasta que transcurra un tiempo desde pulsado el boton
  // Luego lo apaga
  Serial.println("Enciende el LED, se queda esperando X tiempo al Pulsador B para apagarlo...");
  led.on();
  botonPullDown.pushStart(START_TIME);
  led.off();

  // Genera un callback, en este caso para destellar un LED hasta que se pulse el boton
  // Si la funcion a pasar como argumento no tiene la misma firma, se debera usar una
  // funcion lambda tal cual el siguiente ejemplo:
  auto callback = []() {
    led.blinkStart(300);
  };
  
  Serial.println("Inicia el destello del LED hasta que se pulse A...");
  botonPullUp.pushStart(callback);

  Serial.println("Inicia el loop()");
}

void loop() {

  // Lee el estado del pulsador Pull-Up
  bool statusButtonA = botonPullUp.push();
  if (statusButtonA) Serial.println(statusButtonA);

  // Lee el estado del pulsador Pull-Down
  bool statusButtonB = botonPullDown.push();
  if (statusButtonB) Serial.println(statusButtonB);
}