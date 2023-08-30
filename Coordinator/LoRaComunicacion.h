/*
  LoRaComunicacion.cpp - Libreria para el uso de envio y recepcion de los
  mensajes mediante comunicación LoRa.
  Creado por José Miguel Pereira Pontón
  Released into the public domain.
*/

#ifndef LoRa_Envio_Recepcion_H
#define LoRa_Envio_Recepcion_H

#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>

void comunicacionLoRaActuador(byte inicial, byte destino, byte origen, int Aireador_val);
void onReceive(int packetSize);

#endif
