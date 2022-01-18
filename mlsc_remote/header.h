

WiFiUDP port;


// LED strip
NeoPixelBrightnessBus<NeoGrbFeature, Neo800KbpsMethod> ledstrip(NUM_LEDS, PixelPin);


void showConnection(bool ledIsOn, bool reconnected, int stateLed) {
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;
  // [Connecting; Reconnected; stateLED; stateLED; stateLED; stateLED; stateLED; stateLED; stateLED; stateLED; stateLED; stateLED;...]
  if (ledIsOn)
  {
    RgbColor pixelOne(255, 0, 0);
    ledstrip.SetPixelColor(0, pixelOne);
  }
  else {
    RgbColor pixelOne(0, 0, 0);
    ledstrip.SetPixelColor(0, pixelOne);
  }

  if (reconnected)
  {
    RgbColor pixelTwo(0, 0, 255);
    ledstrip.SetPixelColor(1, pixelTwo);
  }
  else {
    RgbColor pixelTwo(0, 0, 0);
    ledstrip.SetPixelColor(1, pixelTwo);
  }

  if (stateLed == -1) {
    for (int n = 2; n < 12; n++) {
      RgbColor pixel(0, 255, 0);
      ledstrip.SetPixelColor(n, pixel);
    }
  }
  else {
    for (int n = 2; n < 12; n++) {
      RgbColor pixel(0, 0, 0);
      ledstrip.SetPixelColor(n, pixel);
    }

    int stateLedWithOffset = stateLed + 2;
    RgbColor pixel(0, 255, 0);
    ledstrip.SetPixelColor(stateLedWithOffset, pixel);
  }

  for (int n = 12; n < NUM_LEDS; n++) {
    RgbColor pixel(r, g, b);
    ledstrip.SetPixelColor(n, pixel);
  }
  ledstrip.Show();
}

void wifiConnect() {
  Serial.println("Start wifi connection");
#ifndef  USE_DHCP
  WiFi.config(ip, gateway, subnet);
 #endif
 
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
   WiFi.hostname(MLSC_CLIENT_HOSTNAME);
  Serial.println("wifi begin");
}

void wifiDisconnect() {
  Serial.println("Disconnecting WiFi");
  ledstrip.Begin();//Begin output
  ledstrip.Show();//Clear the strip for use
  WiFi.disconnect(true);
}
