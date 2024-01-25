/*  -- Ultrasonic (Sensor de distancia por ultrasonido) --
 *
 *  Library for Ultrasonic Ranging Module in a minimalist way
 *  created 3 Apr 2014 by Erick Simões (github: @ErickSimoes | twitter: @AloErickSimoes)
 *  Released into the MIT License.
 */

#ifndef Ultrasonic_h
#define Ultrasonic_h

#include "Arduino.h"

/*** Constantes Globales Ultrasonic ***/
static const uint8_t CM   = 28;
static const uint8_t INC  = 71;

class Ultrasonic {
  public:   
    Ultrasonic(uint8_t sigPin) : Ultrasonic(sigPin, sigPin) {};
    Ultrasonic(uint8_t trigPin, uint8_t echoPin, unsigned long timeOut = 20000UL);
    unsigned int read(uint8_t und = CM);
    void setTimeout(unsigned long timeOut) {timeout = timeOut;}

  private:
    uint8_t trig;
    uint8_t echo;
    boolean threePins = false;
    unsigned long previousMicros;
    unsigned long timeout;
    unsigned int timing();
};

#endif