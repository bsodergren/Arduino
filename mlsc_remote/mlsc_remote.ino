#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NeoPixelBrightnessBus.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>

#include "mlsc_props.h"
#include "header.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Serial Begin");

  ledstrip.Begin();//Begin output
  ledstrip.Show();//Clear the strip for use

 // welcomeLight();

  pinMode(LED, OUTPUT); // Initialize the LED pin as an output

  // Connect to wifi and print the IP address over serial
  wl_status_t state;
  bool isOn = false;
  int timeoutCounter = 0;
  bool reconnected = false;
  int stateLED = 0;

  wifiConnect();
  while (WiFi.status() != WL_CONNECTED) {
    reconnected = false;
    stateLED = -1;
    if (timeoutCounter >= 20) {
      reconnected = true;
      delay(500);
      wifiDisconnect();
      delay(500);
      wifiConnect();
      delay(500);
      timeoutCounter = 0;
    }

    state = WiFi.status();
    digitalWrite(LED, HIGH);

    if (state == WL_CONNECTED) {
      stateLED = 0;
      Serial.println("WL_CONNECTED");
    }
    else if (state == WL_NO_SHIELD) {
      stateLED = 1;
      Serial.println("WL_NO_SHIELD");
    }
    else if (state == WL_IDLE_STATUS) {
      stateLED = 2;
      Serial.println("WL_IDLE_STATUS");
    }
    else if (state == WL_NO_SSID_AVAIL) {
      stateLED = 3;
      Serial.println("WL_NO_SSID_AVAIL");
    }
    else if (state == WL_SCAN_COMPLETED) {
      stateLED = 4;
      Serial.println("WL_SCAN_COMPLETED");
    }
    else if (state == WL_CONNECTED) {
      stateLED = 5;
      Serial.println("WL_CONNECTED");
    }
    else if (state == WL_CONNECT_FAILED) {
      stateLED = 6;
      Serial.println("WL_CONNECT_FAILED");
    }
    else if (state == WL_CONNECTION_LOST) {
      stateLED = 7;
      Serial.println("WL_CONNECTION_LOST");
    }
    else if (state == WL_DISCONNECTED) {
      stateLED = 8;
      Serial.println("WL_DISCONNECTED");
    }
    /*
      if (state == WL_NO_SHIELD) {  // WiFi.begin wasn't called yet
      wifiConnect();

      } else if (state == WL_CONNECT_FAILED) {  // WiFi.begin has failed (AUTH_FAIL)
      wifiDisconnect();
      }
    */

    delay(500);
    Serial.print(".");
    showConnection(isOn, reconnected, stateLED);
    isOn = !isOn;
    timeoutCounter++;
  }

  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Hostname: ");
  Serial.println(WiFi.hostname());
  digitalWrite(LED, LOW);

  ledstrip.Show();//Clear the strip for use
  ArduinoOTA.setHostname(host);
  ArduinoOTA.onStart([]() {
    // Code here

  });


  ArduinoOTA.onEnd([]() {
    // Code here

  });

  ArduinoOTA.onError([](ota_error_t error) {
    (void)error;
    ESP.restart();
  });

  /* setup the OTA server */
  ArduinoOTA.begin();

  port.begin(localPort);


}

uint8_t N = 0;
#if PRINT_FPS
uint16_t fpsCounter = 0;
uint32_t secondTimer = 0;
#endif

void loop() {

  ArduinoOTA.handle();

  // Read data over socket
  int packetSize = port.parsePacket();
  // If packets have been received, interpret the command


  ledstrip.SetBrightness(128);


  if (packetSize) {
    int len = port.read(packetBuffer, BUFFER_LEN);
    int n = 0;

    for (int i = 0; i < len; i += 3) {

      RgbColor pixel((uint8_t)packetBuffer[i], (uint8_t)packetBuffer[i + 1], (uint8_t)packetBuffer[i + 2]);
      ledstrip.SetPixelColor(n, pixel);
      n++;
    }
    ledstrip.Show();
#if PRINT_FPS
    fpsCounter++;

    Serial.print("/");//Monitors connection(shows jumps/jitters in packets)
#endif
  }
#if PRINT_FPS
  if (millis() - secondTimer >= 1000U) {
    secondTimer = millis();
    Serial.printf("FPS: %d\n", fpsCounter);
    fpsCounter = 0;
  }
#endif
}
