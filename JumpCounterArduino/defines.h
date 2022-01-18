
#define EEPROM_ADDR 10



//Pin Assignments (You should change these)
const int CLK       = 9;           //Connected to TPIC pin 13: SRCLK (aka Clock)
const int LATCH     = 10;          //Connected to TPIC pin 12: RCLK (aka Latch/load/CS/SS...)
const int OE        = 12;          //Connected to TPIC pin 9: OE (Output Enable)
const int DOUT      = 13;          //Connected to TPIC pin 3: SER (aka MOSI)

const int resetPin = 4;    // the number of the pushbutton pin
const int jumpPin = 2;
const int wakePin = 3;
const int ledPin = 5;

//Number Patterns (0-9)
//***Drains 0-7 must be connected to segments A-DP respectively***
const byte numTable[] =
{
  B11111100,
  B01100000,
  B11011010,
  B11110010,
  B01100110,
  B10110110,
  B10111110,
  B11100000,
  B11111110,
  B11110110,
  B00000000
};

//Global Variables
int numDevices = 1;                       //The number of x-digit display modules you plan to use
int maxDisplays = 1;                      //The maximum displays that could be accommodated (see note 1)
int maxDigits = 4;                        //The maximum digits you plan on displaying per display module (each SR can handle a max of 8 digits)
int SRData[1][4];                         //The storage location for the digit information. We must specify a fixed array at compile time (see note 2)
boolean debug = false;                     //Change to true to print messages
boolean __stayalive = false;

unsigned int laststayaliveTime = 0; 
unsigned int sleep_timer = 1000*60; 

unsigned int sleeping  = 0;
int delayTime = 0;
byte ones = 0, tens = 0, hundreds = 0, thousands = 0;

int number=0,ttime = 50,x = 1;

// Variables will change:
int resetState;             // the current reading from the input pin
int lastresetState = LOW;   // the previous reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;

    
