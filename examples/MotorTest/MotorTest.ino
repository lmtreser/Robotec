/*
 * Motor Test
 * Prueba de dos motores de C.C.
 */

#include <Robotec.h>

// Constantes con pines Motor A
const int ENA = 3;
const int IN1 = 2;
const int IN2 = 4;

// Otras constantes
const int DELAY_TIME = 2000;
const int DELAY_SHORT = 100;

// Pines: ENABLE, IN1, IN2
Motor motorA(ENA, IN1, IN2);

void setup() {

  Serial.begin(9600);
  Serial.println("Start Motor");
}

void loop() {

  // Secuencia: arranque, freno, inversion de marcha
  int velocidad = PWM_MAX;
  motorA.start(velocidad);
  delay(DELAY_TIME);
  motorA.reverse(velocidad);
  delay(DELAY_TIME);
  motorA.brake();
  delay(DELAY_TIME);

  // Secuencia marcha con incremento de velocidad
  for (int i = 0; i < 255; i++) {
    velocidad = i;
    motorA.start(velocidad);
    Serial.print("PWM: ");
    Serial.println(velocidad);
    delay(DELAY_SHORT);
  }
  delay(DELAY_TIME);
  // Secuencia marcha con decremento de velocidad
  for (int j = 255; j > 0; j--) {
    velocidad = j;
    motorA.start(velocidad);
    Serial.print("PWM: ");
    Serial.println(j);
    delay(DELAY_SHORT);
  }
}
