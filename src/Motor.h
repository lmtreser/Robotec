
#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

/*** Constantes Globales Motor ***/
static const uint8_t PWM_MIN = 0;
static const uint8_t PWM_MAX = 255;

/*** Motor DC ***/
class Motor {
  public:
    Motor(uint8_t enablePin, uint8_t in1Pin, uint8_t in2Pin);
    void start(uint8_t pwm);                                   // Iniciar y detener el motor
    void reverse(uint8_t pwm);                                 // Invertir la dirección del motor
    void brake();                                              // Aplicar freno al motor

  private:
    uint8_t _velocidad;
    uint8_t _enablePin;
    uint8_t _in1Pin;
    uint8_t _in2Pin;
  
    void _setSpeed(uint8_t pwm);   // Establecer la velocidad del motor
};

#endif