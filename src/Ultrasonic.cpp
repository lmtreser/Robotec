/*  Ultrasonic - Sensor de distancia por ultrasonido
 *
 *  Library for Ultrasonic Ranging Module in a minimalist way
 *  created 3 Apr 2014 by Erick Simões (github: @ErickSimoes | twitter: @AloErickSimoes)
 *  Released into the MIT License.
 */


#include "Ultrasonic.h"
#include "Arduino.h"

/** @brief Sensor de distancia por ultrasonido
 * @param trigPin Pin fisico **Trigger**
 * @param echoPin Pin fisico **Echo**
 * @param timeOut ---
**/

Ultrasonic::Ultrasonic(uint8_t trigPin, uint8_t echoPin, unsigned long timeOut) {
  trig = trigPin;
  echo = echoPin;
  threePins = trig == echo ? true : false;
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  timeout = timeOut;
}

unsigned int Ultrasonic::timing() {
  if (threePins)
    pinMode(trig, OUTPUT);

  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  if (threePins)
    pinMode(trig, INPUT);

  previousMicros = micros();
  // wait for the echo pin HIGH or timeout
  while (!digitalRead(echo) && (micros() - previousMicros) <= timeout);
  previousMicros = micros();
  // wait for the echo pin LOW or timeout
  while (digitalRead(echo)  && (micros() - previousMicros) <= timeout);

  return micros() - previousMicros; // duration
}

/** @brief Si la unidad de medida no es pasada como un parametro, por defecto,
 *  retornará la distancia en centimetros (**CM**).
 *  @param und **CM** (centimetros) o **INC** (pulgadas)
 *  @return **unsigned int** Valor que representa la distancia
**/
unsigned int Ultrasonic::read(uint8_t und) {
  return timing() / und / 2;  //distance by divisor
}
