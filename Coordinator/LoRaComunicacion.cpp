/*
  LoRaComunicacion.cpp - Libreria para el uso de envio y recepcion de los
  mensajes mediante comunicación LoRa.
  Creado por José Miguel Pereira Pontón
  Released into the public domain.
*/
#include "LoRaComunicacion.h"
#include "VariablesGlobales.h"

// ---------------------- Envío Mensaje LoRa ---------------------
void comunicacionLoRaActuador(byte inicial, byte destino, byte origen, int Aireador_val) {
  // Establecer Conexión LoRa
  Serial.println("LoRa Conectado");
  Serial.print("Envio de paquetes: ");
  // Enviar Datos
  LoRa.beginPacket();
  LoRa.write(inicial);            // Caracter de Inicio
  LoRa.write(destino);           // ID Actuador
  LoRa.write(origen);           // ID Local
  LoRa.write(Aireador_val);    // Señal de Control Aireador - ON/OFF
  LoRa.endPacket();           // Fin de transmisión de paquete
  Serial.println("Paquetes enviados mediante LoRa");
}

// ------------------------- Escuchar LoRa -----------------------
void onReceive(int packetSize) {
  if (packetSize == 0) return;
  //if (packetSize) {
    Serial.println("Data Recibida");
    Serial.println("Leyendo Encabezados");
    // Lectura de los encabezados del mensaje
    identificador = LoRa.read();               // Caracter de Inicio
    recipient = LoRa.read();                  // Direccion de llegada.
    variableAddressSensor = LoRa.read();     // Direccion del emisor del mensaje.
    MensajeLong = LoRa.read();              // Longitud del mensaje
    // Lectura del mensaje 
    MensajeVar = "";
    while (LoRa.available()) {
      MensajeVar += (char)LoRa.read();
    }
    Serial.println("Revision de condiciones");

    // Si la direccion pertenece al coordinador
    if (identificador = ! initAddress_F) {
      Serial.println("No es el caracter de inicio requerido");
      LoRa_Ok = false;
      return;
    }
    if (recipient != localAddress) {
      Serial.println("Este mensaje no es para mi.");
      LoRa_Ok = false;
      return;
    }
    if (MensajeLong != MensajeVar.length()) {   // Revisión por error en la longitud del mensaje
      Serial.println("error: Longitud del mensaje no coincide");
      return;                             // Saltar la función
    }
    
    // Determinacion si la direccion del elemento del nodo sensor pertenece a la lista de equipos
    for (int i = 0; i < elementCount; i++) {
      if (sensoresLista[i] == variableAddressSensor) {
        banderaPertenencia = 1;
        if (banderaPertenencia == 1) {
          index_elem = i;
          variableAddressActuador = actuadoresLista[index_elem]; //Retorno del nodo actuador relacionado.
        }
      }
    }
    if (banderaPertenencia == 0) {
      LoRa_Ok = false;
      return; // Si no tiene pertenencia en los elementos receptores, se retorna y no sigue la funcion
    }
    Serial.println("Informacion Correcta");
    // Determinacion del valor del DO y Temperatura del String
    ind1 = MensajeVar.indexOf(',');                   // Encontrar el primer patron con ","
    DO_s = MensajeVar.substring(0, ind1);            // Captura el primer String
    ind2 = MensajeVar.indexOf(',', ind1+1 );        // Encuentra la ubicación del segundo elemento 
    Temp_s = MensajeVar.substring(ind1+1);         // Captura el segundo String
    // Conversion a números flotantes
    DO = DO_s.toFloat();                      // Conversión a numero flotante
    Temp = Temp_s.toFloat();                 // Conversión a numero flotante
    
    // Print de mensajes
    Serial.println("Enviado de: 0x" + String(variableAddressSensor, HEX));
    Serial.println("Recibido en: 0x" + String(recipient, HEX));
    Serial.println("Nodo Actuador Relacionado: 0x" + String(variableAddressActuador, HEX));
    Serial.println("Oxigeno Disuelto: " + String(DO));
    Serial.println("Temperatura: " + String(Temp));
    Serial.println("RSSI: " + String(LoRa.packetRssi()));
    Serial.println("Snr: " + String(LoRa.packetSnr()));
    Serial.println();
    //
    LoRa_Ok = true;
    banderaPertenencia = 0;
    index_elem = 0;
    packetSize = 0;
  //}
}
