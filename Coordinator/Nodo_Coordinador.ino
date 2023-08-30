/*                    Sección del Nodo Coordinador
    Realizado por: José Miguel Pereira Pontón
    Este código realiza la recepción de las variables Oxígeno Disuelto y Temperatura
    que provienen de las piscinas camaroneras.
    Con los valores recibidos, se realiza el Control Difuso, para determinar la salida
    en base de funciones de membresía.
*/

// --------------------------- Librerias ---------------------------
#include <SPI.h>                            // Librería de comunicación en bus SPI
#include <LoRa.h>                          // Librería de comunicación LoRa
#include <WiFi.h>                         // Librería de uso de WiFi
#include <U8g2lib.h>                     // Librería para uso de la pantalla Oled
#include <Fuzzy.h>                      // Librería para el control difuso
#include "secrets.h"                   // Librería Creada para contraseñas de internet y ThingSpeak
#include "LoRaComunicacion.h"         // Librería Creada para modular el uso de la comunicación LoRa
#include "Setup_Fuzzy.h"             // Librería Creada para modular las configuraciones del control difuso
//#include "ThingSpeak_Internet.h"    // Librería Creada para modular las configuraciones del Internet y ThingSpeak
#include "ThingSpeak.h"            // Librería para comunicación con ThingSpeak
// ---------------------------- Objetos ----------------------------
Fuzzy *fuzzy = new Fuzzy();
// --------------------------- LoRa Radio---------------------------
#define BAND  915E6
#define LORA_SCK 5             // GPIO5 - SX1276 SCK
#define LORA_MISO 19          // GPIO19 - SX1276 MISO
#define LORA_MOSI 27         // GPIO27  - SX1276 MOSI
#define LORA_CS 18          // GPIO18   - SX1276 CS
#define LORA_RST 14        // GPIO14    - SX1276 RST
#define LORA_IRQ 26       // GPIO26     - SX1276 IRQ (interrupt request)
// --------------------------- I2C OLED ----------------------------
#define OLED_SDA 4      // GPIO 4  - Data
#define OLED_SCL 15    // GPIO 15  - Clock
#define OLED_RST 16   // GPIO 16   - Reset
// --------------------------- Variables ---------------------------
// --------------------- Variables Analogicas ----------------------
float DO = 0;
float Temp = 0;
int Aireadores = 0;
String MensajeVar;
byte MensajeLong;
byte MensajeLong_i;
int ind1;
int ind2;
String DO_s;
String Temp_s;
// --------------------- Bytes de informacion ----------------------
byte initAddress_F = 0xFF;                            // Dirección de Broadcast
byte localAddress = 0xFF;                          // Direccion Local             - (Nodo Coordinador)
byte destinationAddress_S1 = 0xBB;                // Direccion Destino            - (Nodo Sensor 1)
byte destinationAddress_A1 = 0xCC;               // Direccion Destino             - (Nodo Actuador 1)
byte destinationAddress_S2 = 0xDD;              // Direccion Destino              - (Nodo Sensor 1)
byte destinationAddress_A2 = 0xEE;             // Direccion Destino               - (Nodo Actuador 1)
byte variableAddressSensor = 0x00;            // Direccion del mensaje de llegada - (Iterante)
byte variableAddressActuador = 0x00;         // Direccion del mensaje de salida   - (Iterante)
byte identificador;                         // Direccion inicial del mensaje      - (Iterante)
byte recipient;                            // Direccion Local                     - (Iterante)
// ----------------------- Lista de equipos ------------------------
byte sensoresLista[] = {destinationAddress_S1, destinationAddress_S2};      // Lista con direcciones de los nodos sensores
byte actuadoresLista[] = {destinationAddress_A1, destinationAddress_A2};   // Lista con direcciones de los nodos actuadores
// ---------------- Lista envio de datos ThingSpeak ----------------
byte listaActualizarIDs[] = {};         // Lista con el ID ordenado de la piscina
float listaActualizarDO[] = {};        // Lista con los valores de Oxígeno Disuelto
float listaActualizarTemp[] = {};     // Lista con los valores de Temperatura
int listaActualizarAireador[] = {};  // Lista con los estados del Aireador
// --------------------- Variables de proceso ----------------------
bool estadoProceso = true;
bool comunicacionEstado = false;
int num_Case = 1; // Número del caso en el que me encuentro
bool LoRa_Ok = false; // Para revisar si lo que receptó por LoRa es válido
int banderaPertenencia = 1; // Para revisar si el objeto enviado es parte de la lista
int index_elem = 1; // indice del elemento dentro de la lista
int contadorDeElementosListas = 0;
int banderaActualizarThingSpeak = 0;
int elementCount = sizeof(sensoresLista);
// -------------------------- ThingSpeak ---------------------------
char ssid[] = SECRET_SSID;     // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;
unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;
String myStatus = "";
// ----------------------------- OLED ------------------------------
//U8G2_SSD1306_128X64_NONAME_F_SW_I2C Display(U8G2_R0, clock, data, reset);
U8G2_SSD1306_128X64_NONAME_F_SW_I2C Display(U8G2_R0, OLED_SCL, OLED_SDA, OLED_RST);
// ------------------------ Control Difuso -------------------------
/*
    Variables de entrada del objeto Fuzzy
    Rangos de las variables de entrada -----------------------------
    -> Variable de oxígeno disuelto:
    Hipox_Acid: 0-2
    Bajo_DO: 2-5
    Normal_DO: 5-8
    Alto_DO: >8
    -> Variable de Temperatura:
    Bajo_T:0-20
    Normal_T: 20-30
    Alto_T: >30
    Rango de la variable de salida ---------------------------------
    Aireador:
    Aireador_Off: 0-0.5
    Aireador_On: 0.5-1
*/
// Entrada Fuzzy --> Oxigeno Disuelto ------------------------------
FuzzySet *Hipox_Acid = new FuzzySet(0, 0, 1, 3);
FuzzySet *Bajo_DO = new FuzzySet(1, 3, 4, 6);
FuzzySet *Normal_DO = new FuzzySet(4, 6, 7, 9);
FuzzySet *Alto_DO = new FuzzySet(7, 9, 18, 18);
// Entrada Fuzzy --> Temperatura -----------------------------------
FuzzySet *Bajo_T = new FuzzySet(-5, -5, 19, 21);
FuzzySet *Normal_T = new FuzzySet(19, 21, 29, 31);
FuzzySet *Alto_T = new FuzzySet(29, 31, 40, 40);
// Salida Fuzzy ---> Aireador --------------------------------------
FuzzySet *Aireador_Off = new FuzzySet(0, 0, 0.3, 0.7);
FuzzySet *Aireador_On = new FuzzySet(0.3, 0.7, 1, 1);

void setup() {
  Fuzzy_Setup();
  // -------------------------------- LoRa -------------------------------
  // LoRa Setup ----------------------------------------------------------
  //SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
  // Configuración para los pines de la comunicación por Radio LoRa
  LoRa.setPins(LORA_CS, LORA_RST, LORA_IRQ);
  //Presentar las razones por las que el ESP32 se despierta
  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa Receptor");
  // Inicializacion de LoRa
  if (!LoRa.begin(915E6)) {
    Serial.println("Establecimiento de conexion LoRa ha Fallado!");
    while (1);
  }
  LoRa.receive();
  Serial.println("LoRa Establecido en la banda 915E6");
  // Palabra de sincronización
  LoRa.setSyncWord(0xF3);
  // ------------------------------- WiFi --------------------------------
  // WiFi Setup
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);  // Inicializar ThingSpeak
  // ------------------------------- OLED --------------------------------
  // OLED Setup ----------------------------------------------------------
  Display.begin();
  Display.enableUTF8Print();    // Habilitar soporte UTF8 para funciones Arduino print()
  Display.setFont(u8g2_font_ncenB08_te);

  // Mensaje Inicial en el OLED
  Display.clearBuffer();
  Display.setCursor(0, 12); Display.print("Caso1: Lectura LoRa");
  Display.sendBuffer();
}

void loop() {
  switch (num_Case) {
    case 1:
      {
        delay(1);
        Serial.println("Caso 1: Lectura LoRa");
        // Obtengo: DO, Temp, byte de envio (Sensor) , byte de destino (Actuador)
        onReceive(LoRa.parsePacket()); 
        //}
        if (LoRa_Ok == true) {
          num_Case = 2;
          Serial.println("Datos por LoRa Receptados Correctamente");
          Serial.println("Envio al Caso 2");
        }
        else {
          num_Case = 1;
          Serial.println("Esperar Data Correcta");
        }
      }
      break;
    case 2:
      // Control Difuso
      LoRa_Ok = false;
      displayEscribir("Caso2: Control Difuso");
      Serial.println("Caso 2: Control Difuso");
      controlDifuso(DO, Temp); // Obtengo el valor Aireadores
      Serial.print("Estado del Aireador actual: ");
      Serial.println(Aireadores);
      num_Case++;
      break;
    case 3:
      // Comunicacion LoRa - Transmision Actuador
      displayEscribir("Caso3: Actuador LoRa");
      Serial.println("Caso 3: Comunicación con LoRa en el Actuador");
      // comunicacionLoRa(byte inicial, byte destino, byte origen, int Aireador_val) 
      comunicacionLoRaActuador(initAddress_F, variableAddressActuador, localAddress, Aireadores);
      num_Case++;
      Serial.println("Datos enviados al Actuador!");
      //LoRa.receive(); 
      break;
    case 4:
      // Comunicacion ThingSpeak
      displayEscribir("Caso4: ThingSpeak");
      Serial.println("Caso 3: Comunicación ThingSpeak");
      // procesoThingSpeak(float DO_Value_TS, float Temp_Value_TS, int Aireador_Value_TS, byte IDs_TS){
      procesoThingSpeak(DO, Temp, Aireadores, variableAddressSensor);
      num_Case = 1;
      Serial.println("Datos actualizados en ThingSpeak!");
      // Comunicacion LoRa - Lectura
      delay(3000);
      Display.clearBuffer();
      Display.setCursor(0, 12); Display.print("Caso1: Lectura LoRa");
      Display.sendBuffer();
      break;
  }
}

void displayEscribir (String palabraEscribir) {
  Display.clearBuffer();
  Display.setCursor(0, 12); Display.print(palabraEscribir);
  Display.sendBuffer();
}

void procesoThingSpeak(float DO_Value_TS, float Temp_Value_TS, int Aireador_Value_TS, byte IDs_TS) {
  // Conexión o reconexión a WiFi
  int contadorConexion = 0;
  if (WiFi.status() != WL_CONNECTED) {
    //Serial.print("Intentando conectar al SSID: ");
    //Serial.println(SECRET_SSID);
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, pass);  // Conexión a una red WPA/WPA2.
      Serial.println("Conectando...");
      contadorConexion++;
      delay(2000);
      // Si no se conecta en 10 intentos se actualiza lista
      if (contadorConexion == 10) {
        Serial.println("Revisar Conexion - No se pudo actualizar");
        banderaActualizarThingSpeak = 1;
        listaActualizarIDs[contadorDeElementosListas] = IDs_TS;
        listaActualizarDO[contadorDeElementosListas] = DO_Value_TS;
        listaActualizarTemp[contadorDeElementosListas] = Temp_Value_TS;
        listaActualizarAireador[contadorDeElementosListas] = Aireador_Value_TS;
        contadorDeElementosListas ++;
        return;
      }
      delay(1000); // Cada 1 segundo
    }
    Serial.println("\nConectado!.");
  }
  // Setear a los campos con los valores obtenidos.
  ThingSpeak.setField(1, DO_Value_TS); // Primer campo - DO
  ThingSpeak.setField(2, Temp_Value_TS); // Segundo campo - Temperatura
  ThingSpeak.setField(3, Aireador_Value_TS); // Tercer campo - Estado Aireador
  // Mensaje de Estatus
  if (DO_Value_TS > 0 && DO_Value_TS < 2) {
    myStatus = String("Oxigeno Disuelto esta en estado Hipoxido");
  }
  else if (DO_Value_TS > 2 && DO_Value_TS < 5) {
    myStatus = String("Oxigeno Disuelto esta en estado Bajo");
  }
  else if (DO_Value_TS > 5 && DO_Value_TS < 8) {
    myStatus = String("Oxigeno Disuelto esta en estado Normal");
  }
  else if (DO_Value_TS > 8) {
    myStatus = String("Oxigeno Disuelto esta en estado Alto");
  }
  // Setear el Status
  ThingSpeak.setStatus(myStatus);
  // Escribir al canal de ThingSpeak los campos
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (x == 200) {
    Serial.println("Canal actualizado exitosamente.");
  }
  else {
    Serial.println("Problema al actualizar el canal. Codigo HTTP de error " + String(x));
  }
}
