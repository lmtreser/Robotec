/*
 * LED Test
 * Prueba un LED testigo
 */

#include <Robotec.h>

// Constantes con pines
const int LED_PIN = 8;
const int TIEMPO_A = 100;
const int TIEMPO_B = 500;
const int PULSOS = 10;

// Constructor LED, pin
Led ledBuiltin(LED_BUILTIN);
Led ledEight(LED_PIN);

void setup() {
  
  // Solo con fines de simulacion
  Serial.begin(9600);

}

void loop() {

  /*** Enciende un LED ***/
  //ledBuiltin.on();
  //delay(1000);

  /*** Apaga un LED ***/
  //ledBuiltin.off();
  //delay(1000);

  /*** Cambia el estado de un LED ***/
  //ledBuiltin.toogle();
  //delay(1500);

  /*** blinkStart(TIEMPO): Crea un LED destellante sin limite ***/
  ledBuiltin.blinkStart(TIEMPO_A);
  //ledBuiltin.blinkStop();

    /*** blinkStart(TIEMPO, CANTIDAD DE DESTELLOS): Crea un LED destellante custom ***/
  bool statusLedEight = ledEight.blinkStart(TIEMPO_B, PULSOS);
  if (statusLedEight) Serial.println("Finalizo la ejecucion");

}