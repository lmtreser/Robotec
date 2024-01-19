
#ifndef Button_h
#define Button_h

#include "Arduino.h"

/*** Constantes Globales Button ***/
static const uint8_t PULL_UP = 0;
static const uint8_t PULL_UP_INTERNAL = 2;
static const uint8_t PULL_DOWN = 3;

/*** Pulsador ***/
class Button {
  public:
    Button(uint8_t buttonPin, uint8_t buttonMode);
    bool push();
    void pushStart(uint16_t time);
    void pushStart(void (*callback)());

  private:
    uint8_t _buttonPin;
    uint8_t _buttonMode;
    uint8_t _buttonState;
    uint8_t _buttonLastState;
    uint32_t _timeLast;
    static const uint32_t _TIME_DEBOUNCE = 50;  // Ajustar este valor según sea necesario
};

#endif