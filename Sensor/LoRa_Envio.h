/*
  LoRa_Envio.cpp - Libreria para el envio de valores mediante comunicación LoRa.
  Creado por José Miguel Pereira Pontón
  Released into the public domain.
*/

#ifndef LoRa_Envio_H
#define LoRa_Envio_H

#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>

void comunicacionLoRa(byte inicial, byte destino, byte origen, String Mensaje, byte Mensaje_Long);
#endif
