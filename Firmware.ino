// Introducción a la Electrónica. Ignacio Zamora Sánchez

#include <ESP32Servo.h> // Librería necesaria para el control del servomotor

// --- Definición de Pines ---
const int pinPIR = 2;     // Pin de Entrada (Sensor PIR)
const int pinServo = 13;  // Pin de Salida (Servomotor)
const int pinLED = 5;     // Pin de Salida (LED indicador)

// --- Variables y Objetos ---
Servo dispensador;          // Crea el objeto 'dispensador'
int anguloDispensa = 140;   // Ángulo al que se mueve para que caiga el alimento
int anguloCerrado = 40;     // Ángulo de reposo (tapa cerrada)
bool dispensado = false;    // Indica si ya se ha servido comida

void setup() {
  Serial.begin(115200);     // Inicia el monitor serial
  pinMode(pinPIR, INPUT);   // El PIR es una entrada
  pinMode(pinLED, OUTPUT);  // El LED es una salida

  // Configuración del Servomotor
  dispensador.attach(pinServo);
  dispensador.write(anguloCerrado); // Cierra la tapa
  digitalWrite(pinLED, LOW);        // Apaga el LED

  Serial.println("Comedero Inteligente: Modo EN ESPERA...");
}

void loop() {
  // Lee el estado del sensor PIR
  int hayGato = digitalRead(pinPIR);

  if (hayGato == HIGH) {
    if (dispensado == false) {
      Serial.println(">>> ¡Gato detectado! Dispensando alimento...");

      // Abre el dispensador
      dispensador.write(anguloDispensa);
      digitalWrite(pinLED, HIGH);

      delay(1500); // Espera 1.5 segundos

      // Cierra el dispensador
      dispensador.write(anguloCerrado);
      digitalWrite(pinLED, LOW);

      // Marca que ya se sirvió comida
      dispensado = true;

      Serial.println("Dispensación completada. Servo cerrado.");

      delay(10000); // Espera 10 segundos antes de volver a comprobar
    }
  } else {
    if (dispensado == true) {
      dispensado = false;
      Serial.println("Sistema reiniciado. Listo para la próxima comida.");
    }
    delay(500);
  }
}
