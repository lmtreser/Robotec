/*
 * Biblioteca para la competencia de robotica educativa "Robotec"
 * created 20 Dic 2023
 * by Lucas Martin Treser (github: @lmtreser)
 *
 * *************************************************************************************
 *
 * Utiliza código (o parte de el) de las siguientes bibliotecas:
 *
 * --- Ultrasonic.h ---
 * Library for Ultrasonic Ranging Module in a minimalist way
 * created 3 Apr 2014 by Erick Simões (github: @ErickSimoes | twitter: @AloErickSimoes)
 * Released into the MIT License.
 * --- Ultrasonic.h ---
 * 
 * --- Led.h ---
 * Led - Arduino library
 * https://gitlab.com/yesbotics/libs/arduino/led
 * --- Led.h ---
 * 
 */

#ifndef Robotec_h
#define Robotec_h

/*** Sensor de distancia por ultrasonido ***/
class Ultrasonic {
  public:
    Ultrasonic(uint8_t sigPin) : Ultrasonic(sigPin, sigPin) {};
    Ultrasonic(uint8_t trigPin, uint8_t echoPin, unsigned long timeOut = 20000UL);
    unsigned int read(uint8_t und = CM);
    void setTimeout(unsigned long timeOut) {timeout = timeOut;}

  private:
    static const uint8_t CM = 28;
    static const uint8_t INC = 71;

    uint8_t trig;
    uint8_t echo;
    boolean threePins = false;
    unsigned long previousMicros;
    unsigned long timeout;
    unsigned int timing();
};

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

/*** Motor DC ***/
class Motor {
  public:
    Motor(uint8_t enablePin, uint8_t in1Pin, uint8_t in2Pin);
    void start(uint8_t pwm);                                   // Iniciar y detener el motor
    void reverse(uint8_t pwm);                                 // Invertir la dirección del motor
    void brake();                                              // Aplicar freno al motor

  private:
    static const uint8_t PWM_MIN = 0;
    static const uint8_t PWM_MAX = 255;
    uint8_t _velocidad;
    uint8_t _enablePin;
    uint8_t _in1Pin;
    uint8_t _in2Pin;
  
    void _setSpeed(uint8_t pwm);   // Establecer la velocidad del motor
};

/*** LED Testigo ***/
class Led {
  public:
    Led(uint8_t ledPin);
    void on();                                         // Enciende
    void off();                                        // Apaga
    void toogle();                                     // Cambia el estado
    void blinkStart(uint16_t time);                    // Destello, ejecutar en loop()
    void blinkStart(uint16_t time, int8_t pulses = 0); // Destello, ejecutar en loop()
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
