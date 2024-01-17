#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "Motores.h"

const char* ssid = "INFINITUMB6AD";
const char* password = "Tp6Dd4Gc1x";
const char* apiURL = "https://app.saulgomezc.site/excavadora/getStatusExcavadora.php";
char statusCharAnterior = 'h';

void Web_setup(){
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado a WiFi");
}

String getAPIResponse(const String& url) {
  HTTPClient http;
  http.begin(url);
  int httpCode = http.GET();
  String payload = "";
  if (httpCode == HTTP_CODE_OK) {
    payload = http.getString();
  } else {
    Serial.print("Error en la solicitud HTTP: ");
    Serial.println(httpCode);
  }
  http.end();
  return payload;
}

void interpretarJSON(const String& jsonPayload) {
  DynamicJsonDocument jsonDoc(1024);
  deserializeJson(jsonDoc, jsonPayload);
  String statusWeb = jsonDoc[0]["status"];
  char statusChar = statusWeb.charAt(0);
  
  Serial.print(statusChar);
  switch (statusChar) {
    case 'u':
      MoverMotores(velocidad,CW,CW);
      EncenderLED(ledUR);
      EncenderLED(ledUL);
      statusCharAnterior = statusChar;
      break;
    case 'd':
      MoverMotores(velocidad,CCW,CCW);
      EncenderLED(ledDR);
      EncenderLED(ledDL);
      statusCharAnterior = statusChar;
      break;
    case 'r':
      MoverMotores(velocidad,CW,CCW);
      EncenderLED(ledUR);
      EncenderLED(ledDR);
      statusCharAnterior = statusChar;
      break;
    case 'l':
      MoverMotores(velocidad,CCW,CW);
      EncenderLED(ledUL);
      EncenderLED(ledDL);
      statusCharAnterior = statusChar;
      break;
    case 'k':
      Servoplus();
      Serial.println(servoPositionTarget);
      statusCharAnterior = statusChar;
      break;
    case 'm':
      Servominus();
      Serial.println(servoPositionTarget);
      statusCharAnterior = statusChar;
      break;
    case 's':
      Stop(); 
      statusCharAnterior = statusChar;
      break;
    case '0':
      GradosServo(0);
      Serial.println(servoPositionTarget);
      statusCharAnterior = statusChar;
      break;
    case '1':
      GradosServo(45);
      Serial.println(servoPositionTarget);
      statusCharAnterior = statusChar;
      break;
    case '2':
      GradosServo(90);
      Serial.println(servoPositionTarget);
      statusCharAnterior = statusChar;
      break;
    case '3':
      GradosServo(135);
      Serial.println(servoPositionTarget);
      statusCharAnterior = statusChar;
      break;
    case '4':
      GradosServo(180);
      Serial.println(servoPositionTarget);
      statusCharAnterior = statusChar;
      break;
    case 'a':
      ApagarLEDVel();
      velocidad = 37;
      EncenderLED(ledLOW);
      statusCharAnterior = statusChar;
      break;
    case 'b':
      ApagarLEDVel();
      velocidad = 44;
      EncenderLED(ledMID);
      statusCharAnterior = statusChar;
      break;
    case 'c':
      ApagarLEDVel();
      velocidad = 99;
      EncenderLED(ledHIGH);
      statusCharAnterior = statusChar;
      break;
    case 'v':
      if (statusCharAnterior != 'v'){
        GirarDerecha();
        statusCharAnterior = statusChar;
      }
      break;
    case 'w':
      if (statusCharAnterior != 'w'){
        GirarIzquierda();
        statusCharAnterior = statusChar;
      }
      break;
    case 'x':
      if (statusCharAnterior != 'x'){
        Demo_Velocidad();
        statusCharAnterior = statusChar;
      }
      break;
    case 'y':
      if (statusCharAnterior != 'y'){
        Negar();
        statusCharAnterior = statusChar;
      }
      break;
    case 'z':
      if (statusCharAnterior != 'z'){
        Bailar();
        statusCharAnterior = statusChar;
      }
      break;
    default:
      Stop();
      statusCharAnterior = statusChar;
      break;
  }
}

void Web(){
  String jsonPayload = getAPIResponse(apiURL);
  interpretarJSON(jsonPayload);
  delay(100); 
}
