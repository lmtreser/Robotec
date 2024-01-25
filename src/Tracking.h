/*  -- Tracking --
 *  Parte de la biblioteca "Robotec" 
 *  created 20 Dic 2023
 *  by Lucas Martin Treser
*/

#ifndef Tracking_h
#define Tracking_h

#include "Arduino.h"

/*** Constantes Globales Tracking ***/
static const uint8_t NO_SENSOR = 0; 
static const uint8_t SENSOR_LEFT = 1;
static const uint8_t SENSOR_CENTER = 2;
static const uint8_t SENSOR_RIGHT = 3; 
static const uint8_t SENSOR_LEFT_CENTER = 4;
static const uint8_t SENSOR_RIGHT_CENTER = 5;
static const uint8_t SENSOR_ALL = 6;

/*** Sensor de linea (tracking) ***/
class Tracking {
  public:
    Tracking(uint8_t outPin, bool black = false);
    Tracking(uint8_t lPin, uint8_t cPin, uint8_t rPin, bool black = false);
    // TODO: agregar soporte para sensor "5-Channel IR Tracker"
    uint8_t read();
  
  private:
    uint8_t _readLCR();
    bool _blackLineState;   // valor que entrega el sensor al leer linea negra
    bool _sensorType;       // tipo de sensor, true: triple, false: simple
    uint8_t _state;         // estado de retorno de la lectura del sensor
    uint8_t _outPin;        // sensor simple: pin out
    uint8_t _lPin;          // sensor triple: pin izquierdo
    uint8_t _cPin;          // sensor triple: pin central
    uint8_t _rPin;          // sensor triple: pin derecho
};

#endif