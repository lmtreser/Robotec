/*  -- Led --
 *  Parte de la biblioteca "Robotec" 
 *  created 20 Dic 2023
 *  by Lucas Martin Treser
*/

#include "Led.h"
#include "Arduino.h"

/** @brief LED testigo 
 *  @param ledPin Pin fisico donde se conecta el LED
**/
Led::Led(uint8_t ledPin) {

  _ledPin = ledPin;
  _statusLed = false;
  _blinkStopValue = false;
  _blinkFlag = false;
  _blinkPulses = 0;
  _lastMillis = 0;

  pinMode(_ledPin, OUTPUT);
}

/** @brief Enciende un LED **/
void Led::on() {
  digitalWrite(_ledPin, HIGH);
}

/** @brief Apaga un LED **/
void Led::off() {
  digitalWrite(_ledPin, LOW);
}

/** @brief Cambia el estado de un LED **/
void Led::toogle() {
  _statusLed = !_statusLed;
  digitalWrite(_ledPin, _statusLed);
}

/** @brief Detiene el destello de un LED iniciado por _blinkStart()_ **/
void Led::blinkStop() {
  _blinkStopValue = true;
}

/** @brief Inicia el destello de un LED, ejecutar en _loop()_.
 *  @param time Tiempo (en mS) entre cambios de estado, tipo **uint16_t**
**/
void Led::blinkStart(uint16_t time) {
  
  uint16_t blinkTime = time;
  uint32_t currentMillis = millis();

  if (!_blinkStopValue) {    
    if (currentMillis - _lastMillis >= blinkTime) {
      _lastMillis = currentMillis;
      toogle();
    }
  }
}

/** @brief Inicia el destello de un LED, ejecutar en _loop()_.
 *  El parametro _pulses_ establece la cantidad de destellos, al finalizar devuelve **true**
 *  @param time Tiempo (en mS) entre cambios de estado, tipo **uint16_t**
 *  @param pulses Cantidad de veces que debera hacer los cambios de estado, tipo **uint8_t**
**/
bool Led::blinkStart(uint16_t time, uint8_t pulses) {

  // Solo se ejecuta si "pulses" esta configurado con un entero mayor a 0
  if ((pulses > 0) && (_blinkFlag == false)) {
    _blinkPulses = pulses * 2; // Un pulso se considera como una secuencia ON/OFF
    _blinkFlag = true;
  }

  if (!_blinkStopValue) {
    
    uint16_t blinkTime = time;
    uint32_t currentMillis = millis();

    if (currentMillis - _lastMillis >= blinkTime) {
      
      _lastMillis = currentMillis;
      toogle();
      
      if (_blinkPulses > 0) {
        _blinkPulses--;        
        if (_blinkPulses == 0) {
          blinkStop();
          return true; // Finalizo la ejecucion
        } else {
          return false;
        }
      }
    }
  }
}