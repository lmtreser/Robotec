/*
 * LED Test
 * Prueba un LED testigo
 */

#include <Robotec.h>

// Constantes con pines
const int LED_PIN = 8;
const int TIEMPO = 500;
const int PULSOS = 5;

// Constructor LED, pin
Led ledBuiltin(LED_BUILTIN);
Led ledEight(LED_PIN);

void setup() {
  // Nada para configurar
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
  ledEight.blinkStart(TIEMPO);
  //ledEight.blinkStop();

  /*** blinkStart(TIEMPO, CANTIDAD DE DESTELLOS): Crea un LED destellante custom ***/
  ledBuiltin.blinkStart(TIEMPO, PULSOS);
}