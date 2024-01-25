/*  -- Motor --
 *  Parte de la biblioteca "Robotec" 
 *  created 20 Dic 2023
 *  by Lucas Martin Treser
*/

#include "Motor.h"
#include "Arduino.h"

/** @brief Motor de corriente continua
 *  @param enablePin Pin fisico **ENABLE**
 *  @param in1Pin Pin fisico **IN1**
 *  @param in2Pin Pin fisico **IN2**
**/
Motor::Motor(uint8_t enablePin, uint8_t in1Pin, uint8_t in2Pin) {
  
  _enablePin = enablePin;
  _in1Pin = in1Pin;
  _in2Pin = in2Pin;
  _velocidad = PWM_MIN;

  pinMode(_in1Pin, OUTPUT);
  pinMode(_in2Pin, OUTPUT);
}

/** @brief Enciende el motor en un sentido (marcha)
 *  @param pwm Velocidad opcional, valor **uint8_t**, rango 0-255
**/
void Motor::start(uint8_t pwm) {
  _setSpeed(pwm);
  digitalWrite(_in1Pin, HIGH);
  digitalWrite(_in2Pin, LOW);
}

/** @brief Enciende el motor con la marcha invertida respecto a __start()__
 *  @param pmw Velocidad opcional, valor **uint8_t**, rango 0-255
**/
void Motor::reverse(uint8_t pwm) {
  _setSpeed(pwm);
  digitalWrite(_in1Pin, LOW);
  digitalWrite(_in2Pin, HIGH);
}

/** @brief Frenar el motor, dejandolo en posición de giro libre **/
void Motor::brake() {
  digitalWrite(_in1Pin, LOW);
  digitalWrite(_in2Pin, LOW);
}

// Set de Velocidad
void Motor::_setSpeed(uint8_t pwm) {
  _velocidad = constrain(pwm, PWM_MIN, PWM_MAX);
  analogWrite(_enablePin, _velocidad);
}