

WiFiUDP port;

// Network information
// IP must match the IP in config.py in python folder
#ifndef USE_DHCP
  IPAddress ip(10, 10, 0, MLSC_CLIENT_IP);
// Set gateway to your router's gateway
  IPAddress gateway(10, 10, 0, 1);
  IPAddress subnet(255, 255, 255, 0);
 #endif
 


// LED strip
NeoPixelBrightnessBus<NeoGrbFeature, Neo800KbpsMethod> ledstrip(NUM_LEDS, PixelPin);

void welcomeLight() {
  Serial.println("Enter welcomeLigth()");
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;

  for (uint8_t i = 0; i < 255; i++) {

    for (int n = 0; n < NUM_LEDS; n++) {
      RgbColor pixel(r, g, b);
      ledstrip.SetPixelColor(n, pixel);
    }
    ledstrip.Show();

    r++;
    g++;
    b++;

    delay(20);
  }
  Serial.println("Leave welcomeLigth()");
}

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
  Serial.println("wifi begin");
}

void wifiDisconnect() {
  Serial.println("Disconnecting WiFi");
  ledstrip.Begin();//Begin output
  ledstrip.Show();//Clear the strip for use
  WiFi.disconnect(true);
}
