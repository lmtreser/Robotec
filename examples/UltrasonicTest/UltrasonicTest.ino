/*
 * Ultrasonic Test
 * Imprime la distancia leida por un sensor de ultrasonidos en
 * centimetros.
 */

#include <Robotec.h>

// Constantes con pines
const int TRIG_PIN = 2;
const int ECHO_PIN = 3;

// Otras constantes
const int DELAY_TIME = 1000;

// Pines Trigger y Echo respectivamente
Ultrasonic ping(TRIG_PIN, ECHO_PIN);

void setup() {

  Serial.begin(9600);
}

void loop() {
  
  int distancia = ping.read();
  Serial.print("Distancia en CM: ");
  Serial.println(distancia);
  delay(DELAY_TIME);
}