#ifndef STASSID
#define STASSID "MLSC-Wifi"
#define STAPSK  "sofie2013"
#endif

#ifndef MLSC_CLIENT_IP
   #define MLSC_CLIENT_IP 1
 #endif

// #define MLSC_CLIENT_IP 14

#if MLSC_CLIENT_IP==11
  const char* host = "OTA-Closet-LEDS";
  #define NUM_LEDS 120

#elif MLSC_CLIENT_IP==12
  const char* host = "OTA-Center-LEDS";
  #define NUM_LEDS 120

#elif MLSC_CLIENT_IP==13

  const char* host = "OTA-Wall-LEDS";
  #define NUM_LEDS 120

#elif MLSC_CLIENT_IP==14
  const char* host = "OTA-Left-Center-LEDS";
  #define NUM_LEDS 120

#elif MLSC_CLIENT_IP==15
  const char* host = "OTA-Right-Center-LEDS";
  #define NUM_LEDS 120

#elif MLSC_CLIENT_IP==1
  #define USE_DHCP 1
  const char* host = "OTA-DNS-LEDS";
  #define NUM_LEDS 60

#endif


#define BUFFER_LEN 1024
#define PRINT_FPS 0
#define LED 2
//#define USE_DHCP 1

int val = 0;
uint8_t brightness = 64;

const uint8_t PixelPin = 3;
unsigned int localPort = 7777;


char packetBuffer[BUFFER_LEN];
const char* ssid = STASSID;
const char* password = STAPSK;
