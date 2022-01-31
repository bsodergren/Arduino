
// Meter colour schemes
#define RED2RED 0
#define GREEN2GREEN 1
#define BLUE2BLUE 2
#define BLUE2RED 3
#define GREEN2RED 4
#define RED2GREEN 5
#define HIGHLIGHT_COLOR  TFT_WHITE

#define X_l_LABEL 310
#define X_S_LABEL 310
#define X_P_LABEL 310

#define Y_l_LABEL 30
#define Y_S_LABEL 130
#define Y_P_LABEL 230

#define X_l_TEXT X_l_LABEL
#define X_S_TEXT X_S_LABEL
#define X_P_TEXT X_P_LABEL

#define Y_l_TEXT Y_l_LABEL+15
#define Y_S_TEXT Y_S_LABEL+15
#define Y_P_TEXT Y_P_LABEL+15

int x_sidebar_pos=295;
int y_sidebar_pos=0;
int x_sidebar_height=190;
int y_sidebar_height=110;



// #include <avr/dtostrf.h> // Only needed for Due

#include <TFT_HX8357.h> // Hardware-specific library
#include "fonts.h" 

TFT_HX8357 tft = TFT_HX8357();       // Invoke custom library

#define HX8357_GREY 0x2104 // Dark grey 16 bit colour

uint32_t runTime = -99999;       // time for next update

int xpos = 100, ypos = 5, gap = 4, radius = 52;
int reading = 0; // Value to be displayed


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



void updatebox(int x, int y, char *string)
{
  tft.setCursor(x, y);
  tft.setTextSize(1);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setFreeFont(FSB18);
  tft.print(string);
 
}


void updatedisplayVal(int x, int y, int n, int p=0)
{
  unsigned int bgcolor=TFT_WHITE;
  if ( p == 1) bgcolor=HIGHLIGHT_COLOR;
  if ( p == 2) bgcolor=HIGHLIGHT_COLOR;
  if ( p == 3) bgcolor=HIGHLIGHT_COLOR;
  
  tft.fillRoundRect(x, y, 160, 50, 5,bgcolor);
  tft.drawRoundRect(x, y, 160, 50, 5,TFT_BLACK);
  tft.drawRoundRect(x-1, y+1, 160-1, 50+1, 5,TFT_BLACK);
  tft.drawRoundRect(x-2, y+2, 160-2, 50+2, 5,TFT_BLACK);
  tft.setCursor(x+60, y+40);
  tft.setTextSize(1);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setFreeFont(FSB18);
  tft.print(n);
  p=0;
}

void drawHome()
{
  tft.fillScreen(TFT_BLACK);  
  tft.fillRoundRect(x_sidebar_pos,y_sidebar_pos,x_sidebar_height,y_sidebar_height,10,TFT_WHITE);  
  
  updatebox(X_l_LABEL, Y_l_LABEL,"Lift Size");
  if(__PRESS_20 == 1)  updatebox(X_S_LABEL, Y_S_LABEL,"Streams");
  if(__PRESS_20 ==  1)  updatebox(X_P_LABEL, Y_P_LABEL,"Products");
}

void updateLiftSize(int value,int p=0)
{
  EEPROMWritelong(EEPROM_ADDR_L, value);
  updatedisplayVal(X_l_TEXT, Y_l_TEXT,value,p);
}

void updateProducts(int value,int p)
{
  EEPROMWritelong(EEPROM_ADDR_P, value);
  updatedisplayVal(X_P_TEXT, Y_P_TEXT,value,p);
}

void updateStreams(int value,int p)
{
  EEPROMWritelong(EEPROM_ADDR_S, value);
  updatedisplayVal(X_S_TEXT, Y_S_TEXT,value,p);
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
  byte len = 4; if (value > 999) len = 5;
  dtostrf(value, len, 0, buf);
  buf[len] = ' '; buf[len+1] = 0; // Add blanking space and terminator, helps to centre text too!
  // Set the text colour to default
  tft.setTextSize(1);

  

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  // Uncomment next line to set the text colour to the last segment value!
  tft.setTextColor(colour, TFT_BLACK);
  tft.setTextDatum(MC_DATUM);
  // Print value, if the meter is large then use big font 8, othewise use 4
  if (r > 84) {
    tft.setTextPadding(55*3); // Allow for 3 digits each 55 pixels wide
    tft.drawString(buf, x, y, 6); // Value in middle
  }
  else {
    tft.setTextPadding(3 * 14); // Allow for 3 digits each 14 pixels wide
    tft.drawString(buf, x, y, 4); // Value in middle
  }
  tft.setTextSize(1);
  tft.setTextPadding(0);
  return x + r;
}
