/*
  VariablesGlobales.h - Libreria para el uso de las variables
  descritas en el Main, usarlas como variables globales.
*/

#ifndef GLOBAL_VARS_H
#define GLOBAL_VARS_H

// --------------------------- Variables ---------------------------
// --------------------- Variables Analogicas ----------------------
extern float DO;
extern float Temp;
extern int Aireadores;
///
extern String MensajeVar;
extern byte MensajeLong;
extern byte MensajeLong_i;
extern int ind1;
extern int ind2;
extern String DO_s;
extern String Temp_s;
///
// --------------------- Bytes de informacion ----------------------
extern byte initAddress_F;                // Dirección de Broadcast
extern byte localAddress;                     // Direccion Local                   - (Nodo Coordinador)
extern byte destinationAddress_S1;           // Direccion Destino                  - (Nodo Sensor 1)
extern byte destinationAddress_A1;          // Direccion Destino                   - (Nodo Actuador 1)
extern byte destinationAddress_S2;         // Direccion Destino                    - (Nodo Sensor 1)
extern byte destinationAddress_A2;        // Direccion Destino                     - (Nodo Actuador 1)
extern byte variableAddressSensor;       // Direccion del mensaje de llegada       - Iterante
extern byte variableAddressActuador;    // Direccion del mensaje de salida         - Iterante
extern byte identificador;                    // Direccion inicial del mensaje            - (Iterante)
extern byte recipient;  
// ----------------------- Lista de equipos ------------------------
extern byte sensoresLista[];
extern byte actuadoresLista[];
// ---------------- Lista envio de datos ThingSpeak ----------------
extern byte listaActualizarIDs[];
extern float listaActualizarDO[];
extern float listaActualizarTemp[];
extern int listaActualizarAireador[];
// --------------------- Variables de proceso ----------------------
extern bool estadoProceso;
extern bool comunicacionEstado;
extern int num_Case; // Número del caso en el que me encuentro
extern bool LoRa_Ok; // Para revisar si lo que receptó por LoRa es válido
extern int banderaPertenencia; // Para revisar si el objeto enviado es parte de la lista
extern int index_elem ; // indice del elemento dentro de la lista
extern int contadorDeElementosListas;
extern int banderaActualizarThingSpeak;
extern int elementCount;
#endif
