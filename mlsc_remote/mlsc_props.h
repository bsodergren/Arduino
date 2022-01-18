#ifndef STASSID
#define STASSID "MLSC-Wifi"
#define STAPSK  "sofie2013"
#endif

#ifdef MLSC_CLIENT_HOSTNAME
  const char* host = MLSC_CLIENT_HOSTNAME; 
 #endif

  #define USE_DHCP 1
  
  #define NUM_LEDS 60

#define BUFFER_LEN 1024
#define PRINT_FPS 0
#define LED 2
uint8_t brightness = 128;

const uint8_t PixelPin = 3;
unsigned int localPort = 7777;


char packetBuffer[BUFFER_LEN];
const char* ssid = STASSID;
const char* password = STAPSK;
