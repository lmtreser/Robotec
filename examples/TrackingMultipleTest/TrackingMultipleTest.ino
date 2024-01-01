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
   * 0: ningun sensor
   * 1: sensor izquierdo
   * 2: sensor central
   * 3: sensor derecho
   * 4: sensor central e izquierdo
   * 5: sensor central y derecho
   * 6: todos los sensores
  */
  int follow = sensorMultiple.read();

  // Mensajes descriptivos
  switch (follow) {
    case 0:
      Serial.println("Ningun sensor");
      break;
    case 1:
      Serial.println("Sensor izquierdo");
      break;
    case 2:
      Serial.println("Sensor central");
      break;
    case 3:
      Serial.println("Sensor derecho");
      break;
    case 4:
      Serial.println("Sensor central e izquierdo");
      break;
    case 5:
      Serial.println("Sensor central y derecho");
      break;
    case 6:
      Serial.println("Todos los sensores");
      break;
    default:
      Serial.print("Lectura erronea");
  }
  delay(500);
}