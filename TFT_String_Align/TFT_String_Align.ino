/*
Tests string alignment

Normally strings are printed relative to the top left corner but this can be
changed with the setTextDatum() function. The library has #defines for:

TL_DATUM = 0 = Top left
TC_DATUM = 1 = Top centre
TR_DATUM = 2 = Top right
ML_DATUM = 3 = Middle left
MC_DATUM = 4 = Middle centre
MR_DATUM = 5 = Middle right
BL_DATUM = 6 = Bottom left
BC_DATUM = 7 = Bottom centre
BR_DATUM = 8 = Bottom right

L_BASELINE =  9 = Left character baseline (Line the 'A' character would sit on)
C_BASELINE = 10 = Centre character baseline
R_BASELINE = 11 = Right character baseline

So you can use lines to position text like:

  tft.setTextDatum(BC_DATUM); // Set datum to bottom centre
 
 Needs fonts 2, 4, 6, 7 and 8

  #########################################################################
  ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
  ######            TO SELECT THE FONTS YOU USE, SEE ABOVE           ######
  #########################################################################
 */


#include <TFT_HX8357.h> // Hardware-specific library

#include "fonts.h" 
TFT_HX8357 tft = TFT_HX8357();       // Invoke custom library

unsigned long drawTime = 0;

int x, y;  // Coordinates for drawing

void setup(void) {
  Serial.begin(115200);
  tft.init();
  tft.setRotation(1);
  
  tft.fillScreen(TFT_BLACK);
  tft.drawRoundRect(300,0,300,300,10,TFT_RED);
  
}

void loop()
{
  
    tft.fillRoundRect(300,0,300,320,10,TFT_WHITE);

  int pos=0;
  drawDisplayBox(pos,"Lift size");
  drawDisplayBox(pos+105,"Streams");
  drawDisplayBox(pos+210,"Products");
  delay(10);
  
  
}
void drawDisplayBox(int x, char *string)
{
    drawLabelString(310,  x, 170, 60,string);
    drawRecBox(310, x+35, 170, 60);

}
void updatebox(int x, int y, char *string)
{
  tft.setCursor(0, 0, 2);
  tft.println("300");

}
void drawRecBox(int x, int y, int w, int h)
{
 
  tft.drawRoundRect(x, y, w, h, 5,TFT_WHITE);

}

void drawLabelString(int x, int y, int w, int h, char *string)
{
  tft.setTextSize(1);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  //tft.setTextDatum(TC_DATUM);
  int ypos, xpos;
  tft.setFreeFont(FSB18);
  tft.drawString(string, x, y, GFXFF);
}
