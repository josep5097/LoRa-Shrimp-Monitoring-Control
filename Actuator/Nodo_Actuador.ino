/*                      Sección del Nodo Actuador 
    Realizado por: José Miguel Pereira Pontón
    Este código realiza la recepción del parámetro de encender o
    apargar el aireador en función del analisis desarrollado en 
    el nodo coordinador.
*/
// --------------------------- Librerias ---------------------------
#include <SPI.h>
#include <LoRa.h>
#include <U8g2lib.h>
// --------------------------- LoRa Radio---------------------------
#define LORA_SCK 5             // GPIO5 - SX1276 SCK
#define LORA_MISO 19          // GPIO19 - SX1276 MISO
#define LORA_MOSI 27         // GPIO27 -  SX1276 MOSI
#define LORA_CS 18          // GPIO18 -   SX1276 CS
#define LORA_RST 14        // GPIO14 -    SX1276 RST
#define LORA_IRQ 26       // GPIO26 -     SX1276 IRQ (interrupt request)
// --------------------------- I2C OLED ----------------------------
#define OLED_SDA 4      // GPIO 4  - Data
#define OLED_SCL 15    // GPIO 15  - Clock
#define OLED_RST 16   // GPIO 16   - Reset
// ----------------------------- OLED ------------------------------
//U8G2_SSD1306_128X64_NONAME_F_SW_I2C Display(U8G2_R0, clock, data, reset);
U8G2_SSD1306_128X64_NONAME_F_SW_I2C Display(U8G2_R0, OLED_SCL, OLED_SDA, OLED_RST);
// ------------------------------ I/O ------------------------------
#define aireadorPin 36
// --------------------------- Variables ---------------------------
//      Bytes de informacion
byte initAddress_F = 0xFF;                       // Dirección de Broadcast
byte localAddress = 0xCC;                       // Direccion Fuente (Nodo Actuador 1)
byte variableAddressCoordinador = 0xFF;        // Direccion de envio (Nodo Coordinador) 
byte variableAddressSensor = 0x00;            // Direccion del mensaje de llegada - (Iterante)
byte variableAddressActuador = 0x00;         // Direccion del mensaje de salida   - (Iterante)
byte identificador;                         // Direccion inicial del mensaje      - (Iterante)
byte recipient;                            // Direccion Local     
//      Variables Iterante
int num_Case = 1;
int Aireadores = 0;
String aireadorEstado = ""; 
bool LoRa_Ok = false;

void setup() {
  // Establecer I/O
  pinMode(aireadorPin, OUTPUT);
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
  // OLED Setup ----------------------------------------------------------
  Display.begin();
  Display.enableUTF8Print();    // Habilitar soporte UTF8 para funciones Arduino print()
  Display.setFont(u8g2_font_ncenB08_te);
  // Mensaje Inicial en el OLED
  Display.clearBuffer();
  Display.setCursor(0, 12); Display.print("LoRa Actuador!");
  Display.sendBuffer();
}

void loop() {
  switch (num_Case) {
    case 1:
      // Se inicia escuchando el mensaje LoRa.
      Serial.println("Caso 1");
      Display.clearBuffer();
      Display.setCursor(0,12); Display.print("Recibiendo datos");
      Display.sendBuffer();
      onReceive(LoRa.parsePacket()); // Obtengo aireador, byteEnvio
      if (LoRa_Ok == true){
        num_Case++;
      }
      else {
        num_Case = 1;
      }
      break;
    case 2:
      // Se acciona el aireador en función de la entrada.
      if (Aireadores == 1){
        digitalWrite(aireadorPin, HIGH);
        Serial.println("Aireador Encendido");
      }
      else {
        digitalWrite(aireadorPin, LOW);
        Serial.println("Aireador Apagado");
      }
      num_Case = 1;
      LoRa_Ok = false;
      break;
  }
}

void onReceive(int packetSize) {
  if (packetSize == 0) return;
  //if (packetSize) {
    Serial.println("Data Recibida");
    Serial.println("Leyendo Encabezados");
    // Lectura de los encabezados del mensaje
    identificador = LoRa.read();               // Caracter de Inicio
    recipient = LoRa.read();                  // Direccion de llegada.
    variableAddressSensor = LoRa.read();     // Direccion del emisor del mensaje.
    // Lectura del mensaje 
    Aireadores = LoRa.read();
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
    if (Aireadores == 1) {
      aireadorEstado == "Encendido";
    }
    else {
      aireadorEstado == "Apagado";
    }
    
  // Print de mensajes
    Serial.println("Enviado de: 0x" + String(variableAddressSensor, HEX));
    Serial.println("Recibido en: 0x" + String(recipient, HEX));
    Serial.println("Aireador: " + String(Aireadores));
    Serial.println("RSSI: " + String(LoRa.packetRssi()));
    Serial.println("Snr: " + String(LoRa.packetSnr()));
    Serial.println();
    //
    LoRa_Ok = true;
}
