
#include "Button.h"
#include "Arduino.h"

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
 *  segun el tiempo especificado por **time**
 *  @param time Tiempo (en mS) en salir del bucle, tipo **uint16_t**
**/
void Button::pushStart(uint16_t time) {

  bool pushStartExit = true;
  uint16_t pushStartDelay = time;
  
  while (pushStartExit) {
    bool pulsaRead = push();
    if (pulsaRead == HIGH) pushStartExit = false;
  }
  delay(pushStartDelay);
}

/** @brief Lee el estado de un Pulsador y genera un callback
 *  @param void (*callback)() Funcion a ejecutar, si la firma no coincide
 *  habra que valerse de una funcion lambda para enmascarar la funcion a pasar,
 *  por ejemplo:   auto callback = []() { funcion_a_enmascarar(parametro); };
**/
void Button::pushStart(void (*callback)()) {
  
  bool pushStartExit = true;
  
  while (pushStartExit) {
    bool pulsaRead = push();
    if (pulsaRead == HIGH) pushStartExit = false;
    (*callback)();
  }
}