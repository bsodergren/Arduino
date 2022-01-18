/*
  Code for interfacing with 7 segment displays
 using the multiplexing method
 and the TPIC6B595 Shift Register (1 per digit)
 By K.O.
 */

#include <EEPROM.h>

#include "MyDebounce.h"
#include "defines.h"
#include "display.h"
#include "func.h"
#include "sleep.h"


MyDebounce resetButton(resetPin,55,true); // Button1 debounced, with default 50ms debounce time.
MyDebounce JumpButton(jumpPin, 55,true); // Button2 debounced, with custom debounce time.

void setup()
{
  Serial.begin(9600);
  
  //Set pin modes
  pinMode(resetPin, INPUT_PULLUP);
  pinMode(jumpPin, INPUT_PULLUP); // Also works with INPUT_PULLUP
  pinMode(wakePin, INPUT_PULLUP);

  pinMode(ledPin,OUTPUT);
   
  pinMode(CLK,OUTPUT);
  pinMode(LATCH,OUTPUT);
  pinMode(DOUT, OUTPUT);
  pinMode(OE, OUTPUT);
    
  //7-Segment Display Init
  digitalWrite(OE,LOW);        //Enables SR Operation
  initializeSRData();          //Prepares SR and clears data on serial line
  digitalWrite(ledPin,HIGH);  
  laststayaliveTime = millis();
  
  number = EEPROMReadlong(EEPROM_ADDR);
  JumpButton.setCount(number);  
    split(number); 
    write_number();
}

void loop()
{ 
  
 refreshDisplay(); 

  if (__stayalive == true) {
      laststayaliveTime = millis();
  }
  sleeping = millis() - laststayaliveTime;  // this keeps getting 0 when it's still dark
  if(sleeping >= sleep_timer ){
      clearDisplay(0);
      enterSleep();
  }
  __stayalive = false;

  if (JumpButton.read() == 1)
  {
   __stayalive=true;
    number=JumpButton.count()+1;
    EEPROMWritelong(EEPROM_ADDR, number);
    split(number); 
    write_number();
    
  
  }

  
  if (resetButton.read() == 1)
  {
    __stayalive=true;
    JumpButton.resetCount();
    number=0;
    clearDisplay(0);
    split(number); 
    write_number();
    EEPROMWritelong(EEPROM_ADDR, number);

  }
  refreshDisplay(); 
  
}
