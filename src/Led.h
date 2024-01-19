/*  -- Led --
 *  Parte de la biblioteca "Robotec" 
 *  created 20 Dic 2023
 *  by Lucas Martin Treser
*/

#ifndef Led_h
#define Led_h

#include "Arduino.h"

/*** LED Testigo ***/
class Led {
  public:
    Led(uint8_t ledPin);
    void on();                                         // Enciende
    void off();                                        // Apaga
    void toogle();                                     // Cambia el estado
    void blinkStart(uint16_t time);                    // Destello, ejecutar en loop()
    bool blinkStart(uint16_t time, uint8_t pulses);    // Destello controlado, ejecutar en loop()
    void blinkStop();                                  // Finaliza el destello

  private:
    bool _statusLed;
    bool _blinkStopValue;
    bool _blinkFlag;
    uint8_t _blinkPulses;
    uint8_t _ledPin;
    uint32_t _lastMillis;
};

#endif