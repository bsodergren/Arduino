// include the library code:
#include <LiquidCrystal.h>

LiquidCrystal lcd(8,9,4,5,6,7);

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

/*-----( Declare Variables )-----*/
int lcd_key       = 0;
int adc_key_in    = 0;
int adc_key_prev  = 0;

#define INTERRUPT_INPUT 2
#define LCD_REFRESH_INTERVAL_MS 100

int ledPin = 3;
int pulse_counter = 1;


#define HOLD 500


boolean fireStabber = false;
boolean pin_active = false ;

unsigned long pin_starttime ;


int lift_size = 200;

char strpulse_counter[5];
char strlift_size[5];

int liftsizeLen;


void check_pin()
{
  if (pin_active)   // pin active, only check for timeout
  {
    if (millis () - pin_starttime >= HOLD)  // wraparound-safe timeout test
    {
      pin_active = false ;   // change state
      digitalWrite (ledPin, LOW) ;
    }
  }
  else  // pin not active
  {
    if (fireStabber == true) // just check for button
    {
       pin_active = true ;  // change state to active
       fireStabber = false;
       digitalWrite (ledPin, HIGH) ;
       pin_starttime = millis () ;   // setup for timeout testing
    }  // debouncing not needed since button won't be sensed again for a miniute...
  }
}



void interrupt_handler()
{
  
  if( pulse_counter >= lift_size )
  {
    fireStabber = true;
    pulse_counter = 0;
    String str="";
    lcd.setCursor(0, 1);

    for(int i = 0; i < 16; i++) {
        str += " ";  
    }
    lcd.print(str);
  }  

  lcd.setCursor(0, 1);
  pulse_counter = pulse_counter + 1;

  sprintf(strpulse_counter, "%3d",pulse_counter);  
  lcd.print(strpulse_counter);
delay(50);
}

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Lift Size");
  liftsizeLen = sprintf(strlift_size, "%5d",lift_size); 
  lcd.setCursor(16-liftsizeLen,0);
  lcd.print(strlift_size);

  // Print a message to the LCD.
  pinMode(ledPin, OUTPUT);
digitalWrite(ledPin, LOW);
     
  // For noise suppression, enable pullup on interrupt pin
  digitalWrite(INTERRUPT_INPUT, HIGH);
  attachInterrupt(INTERRUPT_INPUT - 2,
                  interrupt_handler,
                  RISING);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
   check_pin();
delay(100);
  adc_key_prev = lcd_key ;       // Looking for changes
  
  lcd_key = read_LCD_buttons();  // read the buttons
  switch (lcd_key)               // depending on which button was pushed, we perform an action
    {
    case btnUP:
      { lift_size++;
      updateLiftDisplay();
        break;
      }
    case btnDOWN:
      { 
        if (lift_size > 1 ) {
          lift_size--;
                updateLiftDisplay();
        }

        break;
      }
    }/* --(end switch )-- */
     
}

void updateLiftDisplay()
{
  liftsizeLen = sprintf(strlift_size, "%5d",lift_size); 
  lcd.setCursor(16-liftsizeLen,0);
  lcd.print(strlift_size);
  lcd.setCursor(0,1);
}

int read_LCD_buttons()
{
  adc_key_in = analogRead(0);      // read the value from the sensor 
  delay(50); //switch debounce delay. Increase this delay if incorrect switch selections are returned.
  int k = (analogRead(0) - adc_key_in); //gives the button a slight range to allow for a little contact resistance noise
  if (5 < abs(k)) return btnNONE;  // double checks the keypress. If the two readings are not equal +/-k value after debounce delay, it tries again.
  // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
  // we add approx 50 to those values and check to see if we are close
  if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
  if (adc_key_in < 50)   return btnRIGHT;
  if (adc_key_in < 195)  return btnUP;
  if (adc_key_in < 380)  return btnDOWN;
  if (adc_key_in < 555)  return btnLEFT;
  if (adc_key_in < 790)  return btnSELECT;
  return btnNONE;  // when all others fail, return this...
}
