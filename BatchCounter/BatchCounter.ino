// include the library code:
/*
 An example showing 'ring' analogue meter on a HX8357 TFT
 colour screen

 Needs Fonts 2, 4 and 7 (also Font 6 if using a large size meter)
 */

// Meter colour schemes
#define RED2RED 0
#define GREEN2GREEN 1
#define BLUE2BLUE 2
#define BLUE2RED 3
#define GREEN2RED 4
#define RED2GREEN 5

// #include <avr/dtostrf.h> // Only needed for Due

#include <TFT_HX8357.h> // Hardware-specific library

TFT_HX8357 tft = TFT_HX8357();       // Invoke custom library

#define HX8357_GREY 0x2104 // Dark grey 16 bit colour

uint32_t runTime = -99999;       // time for next update

int reading = 0; // Value to be displayed
int d = 0; // Variable used for the sinewave test waveform
boolean alert = 0;
int8_t ramp = 1;



#define INTERRUPT_INPUT 21
#define INTERRUPT_INPUT_INT 2
int ledPin = 13;
int pulse_counter = 0;
int buttonPin = A9;

int adc_key_val[5] ={ 115, 740, 940,  1010, 1268 };          // Original, works after actually reading the analog0
                                                                                  // You might want to change these values to fit your resistor array
int NUM_KEYS = 5;
int adc_key_in;
int key=-1; 


#define HOLD 500


boolean fireStabber = false;
boolean pin_active = false;

unsigned long pin_starttime;


int lift_size = 50;
int buttonValue;
char strpulse_counter[5];
char strlift_size[5];

int liftsizeLen;

    int xpos = 0, ypos = 5, gap = 4, radius = 52;

void check_pin() {
  


  if (pin_active)  // pin active, only check for timeout
  {
    if (millis() - pin_starttime >= HOLD)  // wraparound-safe timeout test
    {
      pin_active = false;  // change state
      digitalWrite(ledPin, LOW);
    }
  } else  // pin not active
  {
    if (fireStabber == true)  // just check for button
    {
      pin_active = true;  // change state to active
      fireStabber = false;
      digitalWrite(ledPin, HIGH);
      pin_starttime = millis();  // setup for timeout testing
    }                            // debouncing not needed since button won't be sensed again for a miniute...
  }
}



void interrupt_handler() {

  if (pulse_counter >= lift_size) {
    fireStabber = true;
    pulse_counter = 0;
  }

  pulse_counter = pulse_counter + 1;
  delay(50);
}

void setup() {


// pinMode (A10, INPUT);
  tft.begin();
  //Serial.begin(9600);
  tft.setRotation(1);

  tft.fillScreen(HX8357_BLACK);
  // Print a message to the LCD.
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  // For noise suppression, enable pullup on interrupt pin
  digitalWrite(INTERRUPT_INPUT, HIGH);
  attachInterrupt(INTERRUPT_INPUT_INT,interrupt_handler,RISING);
}

void loop() {
  
  adc_key_in = analogRead(A1);    // Read the value from the sensor 
  key = get_key(adc_key_in); 
if (key == 1 ) {
  lift_size=lift_size+5;
}

if (key == 2 ) {
  if(lift_size > 5 ) {
    lift_size=lift_size-5;
  }
}


  char _buf[10];
  byte _len = 3; 
  dtostrf(lift_size, _len, 0, _buf);
//  buf[len] = ' '; buf[len+1] = 0;


  xpos = 480/2 - 160, ypos = 0, gap = 15, radius = 170;

  ringMeter(pulse_counter,1,lift_size, xpos,ypos,radius,_buf,GREEN2RED); // Draw analogue meter

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  check_pin();
  delay(0);
}

int get_key(unsigned int input)
{
    int k;
    for (k = 0; k < NUM_KEYS; k++)    // Start counting
    {
      //if (input == adc_key_val[k])        // Works, but doesn't allow for deviations
      if (input < adc_key_val[k])            // should be more reliable as it looks for a range instead of a fixed value.
 {
      	Serial.println( k);

            return k;                                  // Breaks the for loop
        }
   }
   
    if (k >= NUM_KEYS)k = -1;            // No valid key pressed
    return k;                                          // So break the loop and look for another keypress
}

int ringMeter(int value, int vmin, int vmax, int x, int y, int r, char *units, byte scheme)
{
  // Minimum value of r is about 52 before value text intrudes on ring
  // drawing the text first is an option
  
  x += r; y += r;   // Calculate coords of centre of ring

  int w = r / 3;    // Width of outer ring is 1/4 of radius
  
  int angle = 150;  // Half the sweep angle of meter (300 degrees)

  int v = map(value, vmin, vmax, -angle, angle); // Map the value to an angle v

  byte seg = 3; // Segments are 3 degrees wide = 100 segments for 300 degrees
  byte inc = 6; // Draw segments every 3 degrees, increase to 6 for segmented ring

  // Variable to save "value" text colour from scheme and set default
  int colour = HX8357_BLUE;
 
  // Draw colour blocks every inc degrees
  for (int i = -angle+inc/2; i < angle-inc/2; i += inc) {
    // Calculate pair of coordinates for segment start
    float sx = cos((i - 90) * 0.0174532925);
    float sy = sin((i - 90) * 0.0174532925);
    uint16_t x0 = sx * (r - w) + x;
    uint16_t y0 = sy * (r - w) + y;
    uint16_t x1 = sx * r + x;
    uint16_t y1 = sy * r + y;

    // Calculate pair of coordinates for segment end
    float sx2 = cos((i + seg - 90) * 0.0174532925);
    float sy2 = sin((i + seg - 90) * 0.0174532925);
    int x2 = sx2 * (r - w) + x;
    int y2 = sy2 * (r - w) + y;
    int x3 = sx2 * r + x;
    int y3 = sy2 * r + y;

    if (i < v) { // Fill in coloured segments with 2 triangles
      switch (scheme) {
        case 0: colour = HX8357_RED; break; // Fixed colour
        case 1: colour = HX8357_GREEN; break; // Fixed colour
        case 2: colour = HX8357_BLUE; break; // Fixed colour
        case 3: colour = rainbow(map(i, -angle, angle, 0, 127)); break; // Full spectrum blue to red
        case 4: colour = rainbow(map(i, -angle, angle, 70, 127)); break; // Green to red (high temperature etc)
        case 5: colour = rainbow(map(i, -angle, angle, 127, 63)); break; // Red to green (low battery etc)
        default: colour = HX8357_BLUE; break; // Fixed colour
      }
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, colour);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, colour);
      //text_colour = colour; // Save the last colour drawn
    }
    else // Fill in blank segments
    {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, HX8357_GREY);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, HX8357_GREY);
    }
  }
  // Convert value to a string
  char buf[10];
  byte len = 3; if (value > 999) len = 5;
  dtostrf(value, len, 0, buf);
  buf[len] = ' '; buf[len+1] = 0; // Add blanking space and terminator, helps to centre text too!
  // Set the text colour to default
  tft.setTextSize(1);

  if (value<vmin || value>vmax) {
    drawAlert(x,y+90,50,1);
  }
  else {
    drawAlert(x,y+90,50,0);
  }

  tft.setTextColor(HX8357_WHITE, HX8357_BLACK);
  // Uncomment next line to set the text colour to the last segment value!
  tft.setTextColor(colour, HX8357_BLACK);
  tft.setTextDatum(MC_DATUM);
  // Print value, if the meter is large then use big font 8, othewise use 4
  if (r > 84) {
    tft.setTextPadding(55*3); // Allow for 3 digits each 55 pixels wide
    tft.drawString(buf, x, y, 8); // Value in middle
  }
  else {
    tft.setTextPadding(3 * 14); // Allow for 3 digits each 14 pixels wide
    tft.drawString(buf, x, y, 4); // Value in middle
  }
  tft.setTextSize(1);
  tft.setTextPadding(0);
  // Print units, if the meter is large then use big font 4, othewise use 2
  tft.setTextColor(HX8357_WHITE, HX8357_BLACK);
  if (r > 84) tft.drawString(units, x, y + 60, 4); // Units display
  else tft.drawString(units, x, y + 15, 2); // Units display

  // Calculate and return right hand side x coordinate
  return x + r;
}

void drawAlert(int x, int y , int side, boolean draw)
{
  if (draw && !alert) {
    tft.fillTriangle(x, y, x+30, y+47, x-30, y+47, rainbow(95));
    tft.setTextColor(HX8357_BLACK);
    tft.drawCentreString("!", x, y + 6, 4);
    alert = 1;
  }
  else if (!draw) {
    tft.fillTriangle(x, y, x+30, y+47, x-30, y+47, HX8357_BLACK);
    alert = 0;
  }
}

// #########################################################################
// Return a 16 bit rainbow colour
// #########################################################################
unsigned int rainbow(byte value)
{
  // Value is expected to be in range 0-127
  // The value is converted to a spectrum colour from 0 = blue through to 127 = red

  byte red = 0; // Red is the top 5 bits of a 16 bit colour value
  byte green = 0;// Green is the middle 6 bits
  byte blue = 0; // Blue is the bottom 5 bits

  byte quadrant = value / 32;

  if (quadrant == 0) {
    blue = 31;
    green = 2 * (value % 32);
    red = 0;
  }
  if (quadrant == 1) {
    blue = 31 - (value % 32);
    green = 63;
    red = 0;
  }
  if (quadrant == 2) {
    blue = 0;
    green = 63;
    red = value % 32;
  }
  if (quadrant == 3) {
    blue = 0;
    green = 63 - 2 * (value % 32);
    red = 31;
  }
  return (red << 11) + (green << 5) + blue;
}
