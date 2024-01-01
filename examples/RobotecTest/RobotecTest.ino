/*
    ROBOTEC TEST
    Sketch para probar dispositivos roboticos

    Utiliza la biblioteca "Robotec"
    https://github.com/lmtreser/Bibliotecas-Arduino/tree/main/Robotec

    created 24 Nov 2023
    by Lucas Martin Treser
    modified 22 Dic 2023
    by Lucas Martin Treser
*/

#include <Robotec.h>
#include "pines.h"

// Sensores de distancia
Ultrasonic ultrasonicFrl(ULTRASON_TRIG_1, ULTRASON_ECHO_1);
Ultrasonic ultrasonicIzq(ULTRASON_TRIG_2, ULTRASON_ECHO_2);
Ultrasonic ultrasonicDer(ULTRASON_TRIG_3, ULTRASON_ECHO_3);

// Sensor infrarrojo
//Tracking sensorLineaLeft(TRACKING_1);
//Tracking sensorLineaCenter(TRACKING_2);
Tracking sensorLineaRight(TRACKING_3);

// Motor A y B
Motor motorA(MA_ENABLE, MA_IN1, MA_IN2);
Motor motorB(MB_ENABLE, MB_IN1, MB_IN2);

// LED Testigo
Led led(LED_1);

void setup() {

  // Configurar pin no usado
  pinMode(NO_PIN_1, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.println("Init ok!");
}

void loop() {

  // LED blink
  led.blinkStart(300);
  
  // Leer estado del pulsador
  bool estadoBoton = digitalRead(BOT_START);
  Serial.print("Pulsador: ");
  Serial.println(estadoBoton);

  // Leer estado de sensores de distancia
  int distanciaFrontal = ultrasonicFrl.read();
  int distanciaIzquierda = ultrasonicIzq.read();
  int distanciaDerecha = ultrasonicDer.read();

  Serial.print("Sensor Frontal: ");
  Serial.print(distanciaFrontal);
  Serial.print("\tSensor Izquierda: ");
  Serial.print(distanciaIzquierda);
  Serial.print("\tSensor Derecha: ");
  Serial.println(distanciaDerecha);

  // Leer estado de sensores IR
  //int trackingLeft = sensorLineaLeft.read();  // devuelve HIGH si detecta la linea
  //int trackingCenter = sensorLineaCenter.read();
  int trackingRight = sensorLineaRight.read();

  //Serial.print("Sensor IR Izquierdo: ");
  //Serial.print(trackingLeft);
  //Serial.print("\tSensor IR Central: ");
  //Serial.print(trackingCenter);
  Serial.print("\tSensor IR Derecho: ");
  Serial.println(trackingRight);

  // Activar motores
  int velocidad = 255;
  motorA.start(velocidad);
  motorB.start(velocidad);
  delay(2000);
  motorA.reverse(velocidad);
  motorB.reverse(velocidad);
  delay(2000);
  motorA.brake();
  motorB.brake();
  delay(2000);
}
