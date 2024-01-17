#include "Motores.h"
#include "Web.h"

int TRIG1 = 16;
int ECHO1 = 17;
int TRIG2 = 2;
int ECHO2 = 4;
unsigned long tiempoDeParada = 0;
const unsigned long tiempoDeEspera = 1000; // 1 segundo de espera

void setup() {
  Serial.begin(115200);
  Web_setup();
  Motores_setup();
  pinMode(TRIG1, OUTPUT); 
  pinMode(ECHO1, INPUT); 
  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);
}

void loop() {
  long distanciaFrontal = Ultrasonico(TRIG1, ECHO1);
  long distanciaTrasera = Ultrasonico(TRIG2, ECHO2);
  Serial.print("Frontal: ");
  Serial.print(distanciaFrontal);
  Serial.print(" Trasera: ");
  Serial.println(distanciaTrasera);
  if (distanciaFrontal <= 40 || distanciaTrasera <= 40) {
    if (tiempoDeParada == 0) { // Iniciar el temporizador de parada breve si no está activo
      tiempoDeParada = millis();
      Stop(); // Detenerse si el objeto está demasiado cerca en frente
    } else if (millis() - tiempoDeParada >= tiempoDeEspera) {
      tiempoDeParada = 0;
      Web();
    }
  } else {
    tiempoDeParada = 0;
    Web();
  }
  delay(50);
}
