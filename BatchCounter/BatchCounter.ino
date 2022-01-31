
#define INTERRUPT_INPUT 21
#define INTERRUPT_INPUT_INT 2

int __PRESS_20 = 0;

int pulse_counter = 1;
int pulse_per_rotation=1;
int current_stack = 1;
int lift_size = 50;
int products = 1;
int streams = 1;
int pages=1;
int page=1;
//int highlight_page=0;


#include "func.h"
#include "display.h"
#include "switch.h"


void interrupt_handler()
{

 if (pulse_counter >= lift_size) {
    fireStabber = true;
    pulse_counter = 0;
  }

  pulse_counter = pulse_counter + 1;
  delay(50);
}

void setup()
{
  tft.begin();
  Serial.begin(9600);
  tft.setRotation(1);
  
  pinMode(p12Pin,INPUT);
  int __val = digitalRead(p12Pin);

  if (__val == HIGH) {
    __PRESS_20 = 1;
    pages=3;
  }
    
  
  
  if(__PRESS_20 == 1)
  { 
    y_sidebar_height=320;
  }
  
  drawHome();
  // Print a message to the LCD.
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);

  if( EEPROMexists(EEPROM_ADDR_L) ) {
    lift_size = EEPROMReadlong(EEPROM_ADDR_L);
  } 

  updateLiftSize(lift_size,1);
  
  if(__PRESS_20 == 1) { 
    if( EEPROMexists(EEPROM_ADDR_P) ) {
      products = EEPROMReadlong(EEPROM_ADDR_P);
    }
  
    if( EEPROMexists(EEPROM_ADDR_S)  ) {
      streams = EEPROMReadlong(EEPROM_ADDR_S);
    }

    updateProducts(products,0);
    updateStreams(streams,0);
  }
  
  // For noise suppression, enable pullup on interrupt pin
  digitalWrite(INTERRUPT_INPUT, HIGH);
  attachInterrupt(INTERRUPT_INPUT_INT,interrupt_handler,RISING);
}

void loop() {
  adc_key_in = analogRead(A1);    // Read the value from the sensor 
  key = get_key(adc_key_in); 
Serial.print(adc_key_in); 
Serial.print(" -- "); 
Serial.println(key); 
  if (key == 1 ) {
    if ( page == 1) lift_size=countUp(lift_size,5);
    if(__PRESS_20 == 1) {     
      if ( page == 2) products=countUp(products,1);
      if ( page == 3) streams=countUp(streams,1);
    }
  }
  
  if (key == 2 ) {
    if ( page == 1) lift_size=countDown(lift_size,5);
    if(__PRESS_20 == 1) { 
      if ( page == 2) products=countDown(products,1);
      if ( page == 3) streams=countDown(streams,1);
    }
  }
  

      
    if (key == 3)
    {
        if(__PRESS_20 == 1) {
      page++;
      if (page > pages ) page = 1;
        }
    }
    
    if (key == 4)  {
        if(__PRESS_20 == 1) {
      page--;
      if (page == 0 ) page = pages;
    }
  }
  
  if (key == 5 ) {
    reboot();
  }
 
  if (key > 0)
  {

    int l_highlight = 0,p_highlight = 0, s_highlight = 0;
    if(page == 1) l_highlight = 1;
    if(__PRESS_20 == 1) { 
    
      if(page == 2) p_highlight = 2;
      if(page == 3) s_highlight = 3;
    }
    updateLiftSize(lift_size,l_highlight);
  
    if(__PRESS_20 == 1) { 
    
      updateProducts(products,p_highlight);        
      updateStreams(streams,s_highlight);
    }

  }
 
  
 
  char _buf[10];
  byte _len = 3; 
  dtostrf(lift_size, _len, 0, _buf);
  xpos = 0, ypos = 50, gap = 10, radius = 135;
  
  ringMeter(pulse_counter,1,lift_size, xpos,ypos,radius,_buf,GREEN2RED); // Draw analogue meter
  
  check_pin();
}
