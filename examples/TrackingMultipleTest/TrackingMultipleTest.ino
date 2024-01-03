/*
 * Tracking Multiple Test
 * Imprime en pantalla el estado del sensor tracking multiple (triple)
 */

#include <Robotec.h>

// Constantes pines
const int IZQ_PIN = 7;
const int CEN_PIN = 6;
const int DER_PIN = 5;

// Pin IZQUIERDO, Pin CENTRAL, Pin DERECHO, linea negra = LOW (por defecto)
Tracking sensorMultiple(IZQ_PIN, CEN_PIN, DER_PIN);
// Pin IZQUIERDO, Pin CENTRAL, Pin DERECHO, linea negra = HIGH
// Tracking sensorMultiple(izqPin,cenPin, derPin, true);

void setup() {

  Serial.begin(9600);
}

void loop() {

  /* Segun el estado de los sensores devuelve:
   * (0) NO_SENSOR:           ningun sensor
   * (1) SENSOR_LEFT:         sensor izquierdo
   * (2) SENSOR_CENTER:       sensor central
   * (3) SENSOR_RIGHT:        sensor derecho
   * (4) SENSOR_LEFT_CENTER:  sensor central e izquierdo
   * (5) SENSOR_RIGHT_CENTER: sensor central y derecho
   * (6) SENSOR_ALL:          todos los sensores
  */
  int follow = sensorMultiple.read();

  // Mensajes descriptivos
  switch (follow) {
    case NO_SENSOR:
      Serial.println("Ningun sensor");
      break;
    case SENSOR_LEFT:
      Serial.println("Sensor izquierdo");
      break;
    case SENSOR_CENTER:
      Serial.println("Sensor central");
      break;
    case SENSOR_RIGHT:
      Serial.println("Sensor derecho");
      break;
    case SENSOR_LEFT_CENTER:
      Serial.println("Sensor central e izquierdo");
      break;
    case SENSOR_RIGHT_CENTER:
      Serial.println("Sensor central y derecho");
      break;
    case SENSOR_ALL:
      Serial.println("Todos los sensores");
      break;
    default:
      Serial.print("Lectura erronea");
  }
  delay(500);
}