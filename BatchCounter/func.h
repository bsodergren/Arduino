
#include <EEPROM.h>

#include <avr/wdt.h>

#define EEPROM_ADDR_L 10
#define EEPROM_ADDR_P 15
#define EEPROM_ADDR_S 20

#define HOLD 500
boolean fireStabber = false;
boolean pin_active = false;

unsigned long pin_starttime;

int relayPin = 12;
int p12Pin = 11;
int buttonPin = A9;


boolean EEPROMexists(long address)
{ 
  float Test = EEPROM.read(address);
  
  if (Test > 0)
  {
    return true;
  } else {
    return false;
  }
}
long EEPROMReadlong(long address) {
  long four = EEPROM.read(address);
  long three = EEPROM.read(address + 1);
  long two = EEPROM.read(address + 2);
  long one = EEPROM.read(address + 3);
  
  return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}

void EEPROMWritelong(int address, long value) {
  byte four = (value & 0xFF);
  byte three = ((value >> 8) & 0xFF);
  byte two = ((value >> 16) & 0xFF);
  byte one = ((value >> 24) & 0xFF);
  
  EEPROM.write(address, four);
  EEPROM.write(address + 1, three);
  EEPROM.write(address + 2, two);
  EEPROM.write(address + 3, one);
}
int countUp(int value,int add)
{
  value=value+add;
  return value;
 }

int countDown(int value,int add)
{
    if(value > add ) {
      value=value-add;
    } else {
      value=add;
    }

return value;
  
}

void check_pin() {
  if (pin_active)  // pin active, only check for timeout
  {
    if (millis() - pin_starttime >= HOLD)  // wraparound-safe timeout test
    {
      pin_active = false;  // change state
      
      digitalWrite(relayPin, LOW);

    }
  } else  // pin not active
  {
    if (fireStabber == true)  // just check for button
    {
      pin_active = true;  // change state to active
      fireStabber = false;
      digitalWrite(relayPin, HIGH);

      pin_starttime = millis();  // setup for timeout testing
    }                            // debouncing not needed since button won't be sensed again for a miniute...
  }
}

void reboot() {
  wdt_disable();
  wdt_enable(WDTO_15MS);
  while (1) {}
}
