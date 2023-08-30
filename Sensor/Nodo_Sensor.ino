/*                      Sección del Nodo Sensor
    Realizado por: José Miguel Pereira Pontón
    Este código realiza el sensado de las variables Oxígeno Disuelto y Temperatura
    de las piscinas camaroneras, durante 1 min cada variable.
    Una vez que tiene los valores de las variables, son enviados mediante
    comunicación LoRa al dispositivo Coordinador.
*/

// --------------------------- Librerias ---------------------------
#include <SPI.h>
#include <LoRa.h>
#include <U8g2lib.h>
#include "LecturaAnalogicaPonderada.h"
#include "LoRa_Envio.h"
// --------------------------- LoRa Radio --------------------------
#define LORA_SCK 5        // GPIO5 - SX1276 SCK
#define LORA_MISO 19     // GPIO19 - SX1276 MISO
#define LORA_MOSI 27    // GPIO27 -  SX1276 MOSI
#define LORA_CS 18     // GPIO18 -   SX1276 CS
#define LORA_RST 14   // GPIO14 -    SX1276 RST
#define LORA_IRQ 26  // GPIO26 -     SX1276 IRQ (interrupt request)
#define BAND  915E6
// --------------------------- I2C OLED ----------------------------
#define OLED_SDA 4
#define OLED_SCL 15
#define OLED_RST 16
// ------------------------------ I/O ------------------------------
#define pin_DO 36
#define pin_Temp 39
// --------------------------- Variables ---------------------------
// Variables Analogicas --------------------------------------------
float DO = 0;
float Temp = 0;
String MensajeVar;
byte MensajeLong;
// Variables de proceso --------------------------------------------
bool estadoProceso = true;
bool comunicacionEstado = false;
int num_Case = 1;
// Bytes de informacion --------------------------------------------
byte initAddress = 0xFF;                   // Dirección de Broadcast
byte localAddress = 0xBB;                 // Direccion Fuente (Nodo Piscina 1)
byte destinationAddress = 0xFF;          // Direccion Destino (Nodo Coordinador)
// Deep Sleep ------------------------------------------------------
#define uS_TO_S_FACTOR 1000000ULL      //Factor de conversión para micro segundos a segundos
#define TIME_TO_SLEEP  30             // Tiempo que el ESP32 va a dormir - En segundos
// Variables extras ------------------------------------------------
RTC_DATA_ATTR int bootCount = 0;    // Contador con variable RTC
U8G2_SSD1306_128X64_NONAME_F_SW_I2C Display(U8G2_R0, /* clock=*/ OLED_SCL, /* data=*/ OLED_SDA, /* reset=*/ OLED_RST);
void setup() {
  Serial.begin(115200);
  Display.begin();
  Display.enableUTF8Print();    // Habilitar soporte UTF8 para funciones Arduino print()
  //u8g2_font_ncenB10_tr ó u8g2_font_ncenB10_tf ó u8g2_font_ncenB08_te ó u8g2_font_ncenB08_tn ó u8g2_font_ncenB08_tr
  Display.setFont(u8g2_font_ncenB08_te);  
  //Incrementa con el numero de booteos -- Para Pruebas de control de Deep Sleep
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));
  //SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS); 
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
  // Configuración para los pines de la comunicación por Radio LoRa
  LoRa.setPins(LORA_CS, LORA_RST, LORA_IRQ);
  //Presentar las razones por las que el ESP32 se despierta
  print_wakeup_reason();
  while (!Serial);
  Serial.println("Nodo Sensor");
  if (!LoRa.begin(915E6)) {
    Serial.println("Conexión LoRa Fallida!");
    while (1);
  }
  // Establecer palabra de sincronización
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa conectado a la banda 915E6");
}

void loop() {
  switch (num_Case) {
    case 1:
    {
      // Se inicia el programa realizando la lectura de los sensores analogicos
      Serial.println("Caso 1");
      Display.clearBuffer();
      Display.setCursor(0,12); Display.print("Lecturas");
      Display.sendBuffer();
      DO = lecturaAnalogicaPonderada(pin_DO);
      Temp = lecturaAnalogicaPonderada(pin_Temp);
      // Prueba
      float decimalN = random(0, 99)/100.0;
      DO = random(1,10) + decimalN;
      Temp = random(10,30) + decimalN;
      MensajeVar = String(DO) + "," + String(Temp);
      MensajeLong = MensajeVar.length();
      num_Case++;
    }
      break;
    case 2:
      // Transmision LoRa
      Serial.println("Caso 2");
      Display.clearBuffer();
      Display.setCursor(0,12); Display.print("LoRa Enviando");
      Display.sendBuffer();
      // comunicacionLoRa(initAddress, destinationAddress, localAddress, mensaje, longitudMensaje);
      comunicacionLoRa(initAddress, destinationAddress, localAddress, MensajeVar, MensajeLong);
      delay(2000);
      num_Case++;
      break;
    case 3:
      // Deep Sleep
      Display.clearBuffer();
      Display.setCursor(0,12); Display.print("Dormir");
      Display.sendBuffer();
      Serial.println("Caso 3");
      Serial.println("Voy a dormir ahora");
      esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
      num_Case = 1;
      delay(5000);
      esp_deep_sleep_start();
      break;
  }
}

void print_wakeup_reason() {
  esp_sleep_wakeup_cause_t wakeup_reason;
  wakeup_reason = esp_sleep_get_wakeup_cause();
  switch (wakeup_reason)
  {
    case 1  : Serial.println("Despierto debido a una señal externa usando RTC_IO"); break;
    case 2  : Serial.println("Despierto debido a una señal externa usando RTC_CNTL"); break;
    case 3  : Serial.println("Despierto debido a un temporizador"); break;
    case 4  : Serial.println("Despierto debido al touchpad"); break;
    case 5  : Serial.println("Despierto debido a un programa ULP"); break;
    default :
      Serial.print("Despierto debido a una causas externa del Deep Sleep: ");
      Serial.println(wakeup_reason);
      break;
  }
}
