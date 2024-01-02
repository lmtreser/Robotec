
bool ledStatus = false;

void setup() {
  
  pinMode(13, OUTPUT);
  pinMode(11, INPUT_PULLUP);
  Serial.begin(9600);
  pushStart(3000, led);
  Serial.println("Entrando al loop");
  led();
}

void loop() {
  //Serial.println(push());
  
}

void led() {
  ledStatus = !ledStatus;
  digitalWrite(13, ledStatus);
}
// para el constructor
// Button(uint8_t pin, uint8_t mode);
// void pushStart(uint8_t time);
// void pushStart(uint8_t time, void (*callback)());
void pushStart(uint8_t time, void (*callback)()) {

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

//Variables
int estadoPulsador = LOW;
int ultimoEstado = LOW;
unsigned long tiempoDebounce = 50;  // Ajusta este valor según sea necesario
unsigned long ultimoTiempo = 0;

bool push() {

  // Si es pulldown
  int lecturaPulsador = !digitalRead(11);
  
  // si es pull up no se tiene que negar

  if (lecturaPulsador != ultimoEstado) {
    ultimoTiempo = millis();
  }

  if ((millis() - ultimoTiempo) > tiempoDebounce) {
    if (lecturaPulsador != estadoPulsador) {
      estadoPulsador = lecturaPulsador;
      return (estadoPulsador == HIGH);
    }
  }

  ultimoEstado = lecturaPulsador;
  return false;
} 
