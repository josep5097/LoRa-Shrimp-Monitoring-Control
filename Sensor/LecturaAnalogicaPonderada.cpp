/*
  LecturaAnalogicaPonderada.cpp - Libreria para obtener un valor ponderado cada minuto.
  Creado por José Miguel Pereira Pontón
  Released into the public domain.
*/
#include "LecturaAnalogicaPonderada.h"

float lecturaAnalogicaPonderada(int bitPin) {
  float variableAnalogica = 0.0;
  for (int j = 0; j < 5; j++) { //durante 60 datos en 1min--15
    variableAnalogica += analogRead(bitPin) * 9 / 1023; // [0% - 100%]
    delay(1000);//cada 4 segundo
  }
  variableAnalogica /= 15;//60
  Serial.print("Valor Analogico de: ");
  Serial.println(variableAnalogica);
  return variableAnalogica;
}
