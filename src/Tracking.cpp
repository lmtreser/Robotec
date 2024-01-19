
#include "Tracking.h"
#include "Arduino.h"

/** @brief Sensor de linea simple (tracking y similares)
 *  @param outPin Pin fisico **OUT**
 *  @param black Valor que entrega al detectar una linea negra, por defecto **false**
**/
Tracking::Tracking(uint8_t outPin, bool black = false) {
  
  _blackLineState = black;
  _sensorType = false;
  _outPin = outPin;
  _state = 0;

  pinMode(_outPin, INPUT);
}

/** @brief Sensor de linea triple (Funduino y similares) 
 *  @param lPin Pin fisico **LEFT**
 *  @param cPin Pin fisico **CENTER**
 *  @param rPin Pin fisico **RIGHT**
 *  @param black Valor que entrega al detectar una linea negra, por defecto **LOW**
**/ 
Tracking::Tracking(uint8_t lPin, uint8_t cPin, uint8_t rPin, bool black = false) {
  
  _blackLineState = black;
  _sensorType = true;
  _lPin = lPin;
  _cPin = cPin;
  _rPin = rPin;
  _state = 0;

  pinMode(_lPin, INPUT);
  pinMode(_cPin, INPUT);
  pinMode(_rPin, INPUT);
}

/** @brief Lectura del estado del sensor
 *  @return **uint8_t** _Sensor simple:_ devuelve por defecto **1** si detecta la linea negra
 *  @return **uint8_t** _Sensor triple:_ NO_SENSOR = **0**, SENSOR_LEFT = **1**, SENSOR_CENTER = **2**,
 *  SENSOR_RIGHT = **3**, SENSOR_LEFT_CENTER = **4**, SENSOR_RIGHT_CENTER = **5**, SENSOR_ALL = **6**
**/
uint8_t Tracking::read() {
  
  if (_sensorType == true) {
    _state = _readLCR();
  }
  else {
    uint8_t estado = digitalRead(_outPin);
    _state = (_blackLineState == false) ? !estado : estado;
  }
  return _state;
}

// Lectura sensor triple
uint8_t Tracking::_readLCR() {
  
  uint8_t sensorLeft = digitalRead(_lPin);
  uint8_t sensorCenter = digitalRead(_cPin);
  uint8_t sensorRight = digitalRead(_rPin);

  // Si la linea negra es leida como LOW, se invierte
  if (_blackLineState == false) {
    sensorLeft = !sensorLeft;
    sensorCenter = !sensorCenter;
    sensorRight = !sensorRight;
  }

  if (sensorLeft && !sensorCenter && !sensorRight) return SENSOR_LEFT;
  else if (!sensorLeft && sensorCenter && !sensorRight) return SENSOR_CENTER;
  else if (!sensorLeft && !sensorCenter && sensorRight) return SENSOR_RIGHT;
  else if (sensorLeft && sensorCenter && !sensorRight) return SENSOR_LEFT_CENTER;
  else if (!sensorLeft && sensorCenter && sensorRight) return SENSOR_RIGHT_CENTER;
  else if (sensorLeft && sensorCenter && sensorRight) return SENSOR_ALL;
  else return NO_SENSOR;
}
