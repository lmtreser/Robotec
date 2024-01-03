/**
 * @mainpage 
 * @brief Biblioteca para la competencia de robotica educativa "Robotec"
 * @date created 20 Dic 2023
 * @author Lucas Martin Treser (github: @lmtreser)
 *
 * *************************************************************************************
 *
 * Utiliza código (o parte de el) de las siguientes bibliotecas:
 *
 * --- Ultrasonic.cpp ---
 * Library for Ultrasonic Ranging Module in a minimalist way
 * created 3 Apr 2014 by Erick Simões (github: @ErickSimoes | twitter: @AloErickSimoes)
 * Released into the MIT License.
 * --- Ultrasonic.cpp ---
 * 
 * --- Led.h ---
 * Led - Arduino library
 * https://gitlab.com/yesbotics/libs/arduino/led
 * --- Led.h ---
 * 
**/

#include <Arduino.h>
#include "Robotec.h"

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
  while(!digitalRead(echo) && (micros() - previousMicros) <= timeout);
  previousMicros = micros();
  // wait for the echo pin LOW or timeout
  while(digitalRead(echo)  && (micros() - previousMicros) <= timeout);

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

/** @brief Pulsador (pushbutton) 
 *  @param buttonPin  Pin fisico donde se conecta el Pulsador
 *  @param buttonMode Modos: **PULL_UP_INTERNAL** (resistencia interna), 
 *  **PULL_UP**, **PULL_DOWN**.
**/
Button::Button(uint8_t buttonPin, uint8_t buttonMode) {
  
  _buttonPin = buttonPin;
  _buttonMode = buttonMode;
  _buttonState = LOW;
  _buttonLastState = LOW;
  _timeLast = 0;

  if (_buttonMode == PULL_DOWN) {
    pinMode(_buttonPin, INPUT);
  } else {
    pinMode(_buttonPin, _buttonMode);
  }
}

/** @brief  Lee el estado de un boton 
 *  @return Devuelve **true** si esta presionado, **false** en caso contrario
**/
bool Button::push() {

  uint8_t buttonRead = !digitalRead(_buttonPin);
  
  if (_buttonMode == PULL_DOWN) buttonRead = !buttonRead;
  if (buttonRead != _buttonLastState) _timeLast = millis();
  
  if ((millis() - _timeLast) > _TIME_DEBOUNCE) {
    if (buttonRead != _buttonState) {
      _buttonState = buttonRead;
      return (_buttonState == HIGH);
    }
  }

  _buttonLastState = buttonRead;
  return false;
}

/** @brief Lee el estado de un Pulsador y genera una demora bloqueante (_delay_) 
 *  segun el tiempo especificado 
 *  @param time Tiempo (en mS) entre cambios de estado, tipo **uint16_t**
**/
void Button::pushStart(uint16_t time) {



}

/** @brief Lee el estado de un Pulsador y genera una demora bloqueante (_delay_) 
 *  segun el tiempo especificado 
 *  @param time Tiempo (en mS) entre cambios de estado, tipo **uint16_t**
 *  @param void (*callback)() 
**/
void Button::pushStart(uint16_t time, void (*callback)()) {
  
  bool pushExit = true;
  int pushDelay = time;
  
  while(pushExit){
    int pulsa = push();
      if (pulsa) {
        pushExit = false;
        Serial.println("Press");
      }
      (*callback)();
  }
  delay(pushDelay);
}