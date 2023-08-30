/*
  LoRa_Envio.cpp - Libreria para el envio de valores mediante comunicación LoRa.
  Creado por José Miguel Pereira Pontón
  Released into the public domain.
*/

#include "LoRa_Envio.h"

void comunicacionLoRa(byte inicial, byte destino, byte origen, String Mensaje, byte Mensaje_Long) {
  // Establecer Conexión LoRa
  Serial.println("LoRa Conectado");
  Serial.println("Envío de paquetes mediante comunicación LoRa - Iniciado");
  // Enviar Datos
  LoRa.beginPacket();
  LoRa.write(inicial);         // ID Broadcast
  Serial.println(inicial);
  LoRa.write(destino);        // ID Coordinador
  Serial.println(destino);
  LoRa.write(origen);        // ID Local
  Serial.println(origen);
  LoRa.write(Mensaje_Long); // Longitud del mensaje
  LoRa.print(Mensaje);     // Mensaje enviado: DO + Temp
  Serial.println(Mensaje);
  LoRa.endPacket();       // Fin de transmisión de paquete
  Serial.println("Envío de paquetes mediante comunicación LoRa - Finalizado");
  delay(1000);
}
