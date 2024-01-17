#ifndef MOTORES_H
#define MOTORES_H

extern int velocidad;
extern int servoPositionTarget;
extern int CW;
extern int CCW;
extern int ledUR;
extern int ledUL;
extern int ledDR;
extern int ledDL;
extern int ledLOW;
extern int ledMID;
extern int ledHIGH;

void Motores_setup();
void MoverMotores(int velocidad,int direccion1,int direccion2);
void Stop();
void GradosServo(int grados);
int Servoplus();
int Servominus();
long Ultrasonico(int TRIG, int ECHO);
void EncenderLED(int led);
void ApagarLEDMotores();
void ApagarLEDVel();
void Bailar();
void Demo_Velocidad();
void Negar();
void GirarIzquierda();
void GirarDerecha();

#endif //MOTORES_H
