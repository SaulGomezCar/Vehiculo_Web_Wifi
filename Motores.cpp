//LIBRERIAS-----------------------------------------------------------------------------
#include <ESP32Servo.h>
#include <Robojax_L298N_DC_motor.h>
//PINES---------------------------------------------------------------------------------
const int IN1 = 25;
const int IN2 = 26;
const int ENA = 33;
const int IN3 = 27;
const int IN4 = 14;
const int ENB = 12;
int ledUR = 23;
int ledUL = 22;
int ledDR = 5;
int ledDL = 13;
int ledLOW = 21;
int ledMID = 19;
int ledHIGH = 18;
//VARIABLES-----------------------------------------------------------------------------
Servo servo;  // Crear un objeto Servo
int servoPositionTarget = 90;
int velocidad = 44;
int CW = 1;
int CCW = 2;
const int CHA = 0;
const int CHB = 1;
#define motor1 1 // do not change
#define motor2 2 // do not change
Robojax_L298N_DC_motor vehiculo(IN1, IN2, ENA, CHA,  IN3, IN4, ENB, CHB,true);
//SETUP---------------------------------------------------------------------------------
void Motores_setup(){
  vehiculo.begin();
  servo.attach(32);  // Adjunta el servo al pin 32
  servo.write(servoPositionTarget); // Inicializar el servo en la posición central
  //servoPositionTarget = servoPosition; // Inicializar la posición objetivo
  pinMode(ledUR,OUTPUT);
  pinMode(ledUL,OUTPUT);
  pinMode(ledDR,OUTPUT);
  pinMode(ledDL,OUTPUT);
  pinMode(ledLOW,OUTPUT);
  pinMode(ledMID,OUTPUT);
  pinMode(ledHIGH,OUTPUT);
  digitalWrite(ledMID,HIGH);
}
//FUNCIONES---CW-CW(U),CCW-CCW(D),CW-CCW(R),CCW-CW(L)----CW=1--CCW=2--------------------
void EncenderLED(int led){
  digitalWrite(led,HIGH);
}
void ApagarLEDMotores(){
  digitalWrite(ledUR,LOW);
  digitalWrite(ledUL,LOW);
  digitalWrite(ledDR,LOW);
  digitalWrite(ledDL,LOW);
}
void ApagarLEDVel(){
  digitalWrite(ledLOW,LOW);
  digitalWrite(ledMID,LOW);
  digitalWrite(ledHIGH,LOW);
}
void MoverMotores(int velocidad, int direccion1, int direccion2) {
  ApagarLEDMotores();
  Serial.print("MoverMotores ");
  Serial.println(velocidad);
  vehiculo.rotate(motor1, velocidad, direccion1);
  vehiculo.rotate(motor2, velocidad, direccion2);
}
void Stop(){
  ApagarLEDMotores();
  Serial.println("Stop");
  vehiculo.brake(1);
  vehiculo.brake(2); 
}

void GirarDerecha(){
  if(velocidad = 37){
    velocidad = 37;
    MoverMotores(velocidad,CW,CCW);
    EncenderLED(ledUR);
    EncenderLED(ledDR);
    delay(750);
    Stop();
  }
  
  if(velocidad = 44){
    velocidad = 44;
    MoverMotores(velocidad,CW,CCW);
    EncenderLED(ledUR);
    EncenderLED(ledDR);
    delay(25);
    Stop();
  }
  
  if(velocidad = 99){
    velocidad = 99;
    MoverMotores(velocidad,CW,CCW);
    EncenderLED(ledUR);
    EncenderLED(ledDR);
    delay(10);
    Stop();
  }
}

void GirarIzquierda(){
  if(velocidad = 37){
    velocidad = 37;
    MoverMotores(velocidad,CCW,CW);
    EncenderLED(ledUR);
    EncenderLED(ledDR);
    delay(750);
    Stop();
  }
  
  if(velocidad = 44){
    velocidad = 44;
    MoverMotores(velocidad,CCW,CW);
    EncenderLED(ledUR);
    EncenderLED(ledDR);
    delay(25);
    Stop();
  }
  
  if(velocidad = 99){
    velocidad = 99;
    MoverMotores(velocidad,CCW,CW);
    EncenderLED(ledUR);
    EncenderLED(ledDR);
    delay(10);
    Stop();
  }
}

void GradosServo(int grados) {
  servoPositionTarget = grados;
  servo.write(servoPositionTarget);
}
void Servoplus() {
  int newPos = servoPositionTarget + 15;
  if (newPos > 180) {
    newPos = 180; // Limitar la posición máxima a 180 grados
  }
  servoPositionTarget = newPos; // Actualizar la posición objetivo
  servo.write(servoPositionTarget); // Mover el servo a la nueva posición
}

void Servominus() {
  int newPos = servoPositionTarget - 15;
  if (newPos < 0) {
    newPos = 0; // Limitar la posición mínima a 0 grados
  }
  servoPositionTarget = newPos; // Actualizar la posición objetivo
  servo.write(servoPositionTarget); // Mover el servo a la nueva posición
}
long Ultrasonico(int TRIG, int ECHO){
  long t; //tiempo que demora en llegar el eco
  long d; //distancia en centimetros
  digitalWrite(TRIG, LOW); //Inicializamos el pin con 0
  delayMicroseconds(2); //Parecida a delay pero trabaja con microsegundos
  digitalWrite(TRIG, HIGH); //Endendemos para que envíe la onda ultrasónica
  delayMicroseconds(10); //Durante 10 microsegundos
  digitalWrite(TRIG, LOW); //Apagar el sensor
  t = pulseIn(ECHO, HIGH); //obtenemos el tiempo del pulso
  d = t/59; //escalamos el tiempo a una distancia en cm
  return d;
}
void Bailar(){
  Serial.println("Bailar");
  MoverMotores(44,CW,CW);
  delay(2000);
  Stop();
  delay(1000);
  MoverMotores(44,CCW,CCW);
  delay(2000);
  MoverMotores(44,CW,CCW);
  delay(2000);
  MoverMotores(44,CCW,CW);
  delay(2000);
  Stop();
}

void Negar(){
  Serial.println("Negar");
  Stop();
  GradosServo(135);
  Serial.println(servoPositionTarget);
  delay(500);
  GradosServo(45);
  Serial.println(servoPositionTarget);
  delay(500);
  GradosServo(135);
  Serial.println(servoPositionTarget);
  delay(500);
  GradosServo(45);
  Serial.println(servoPositionTarget);
  delay(500);
  GradosServo(135);
  Serial.println(servoPositionTarget);
  delay(500);
  GradosServo(45);
  Serial.println(servoPositionTarget);
  delay(500);
  GradosServo(90);
  Serial.println(servoPositionTarget);
  delay(500);
  Stop();
}

void Demo_Velocidad(){
  int velocidad = 0;
  Serial.println("Demo Velocidad");
  ApagarLEDVel();
  velocidad = 37;
  EncenderLED(ledLOW);
  MoverMotores(velocidad,CW,CW);
  EncenderLED(ledUR);
  EncenderLED(ledUL);
  delay(1500);
  Stop();
  ApagarLEDVel();
  velocidad = 44;
  EncenderLED(ledMID);
  MoverMotores(velocidad,CW,CW);
  EncenderLED(ledUR);
  EncenderLED(ledUL);
  delay(1500);
  Stop();
  ApagarLEDVel();
  velocidad = 99;
  EncenderLED(ledHIGH);
  MoverMotores(velocidad,CW,CW);
  EncenderLED(ledUR);
  EncenderLED(ledUL);
  delay(1500);
  Stop();
}
