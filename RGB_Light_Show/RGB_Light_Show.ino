#include <Shifter.h>
#define SER_Pin 13 //SER_IN
#define RCLK_Pin 8 //L_CLOCK
#define SRCLK_Pin 12 //CLOCK

#define NUM_REGISTERS 1 //how many registers are in the chain

//initaize shifter using the Shifter library
Shifter shifter(SER_Pin, RCLK_Pin, SRCLK_Pin, NUM_REGISTERS); 

#define REDPIN 10
#define GREENPIN 11
#define BLUEPIN 9
#define FADESPEED 1

int latchPin = 8;
int clockPin = 12;
int dataPin = 13;
int i = 0;

int buttonInt = 0; //AKA digital pin 2
volatile int selectedMode = 1;


int sensorPin = A0;    // select the input pin for the potentiometer

int sensorValue = 0; 
int delayValue = 0;

void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  

  attachInterrupt(buttonInt, swap, RISING);

  Serial.begin(9600);

}
void swap()
{
}

int delaySpeed()
{
   sensorValue = analogRead(sensorPin); 
  delayValue = map(sensorValue, 0, 1023, 20, 500); 
  return delayValue;
}

void rotate()
{
  for (i = 0; i < 8; i++) {
    shifter.clear(); //set all pins on the shift register chain to LOW
    shifter.setPin(i,HIGH); //set pin 1 in the chain(second pin) HIGH

      if( i % 2) {
      red();
    } 
    else {
      blue();
    }
    shifter.write(); //send changes to the chain and display the 

      delay(delaySpeed());

  }
}


void loop() {

 
  
  
  
  

}


void white()
{
  analogWrite(REDPIN, 255);
  analogWrite(GREENPIN, 255);
  analogWrite(BLUEPIN, 255);

}  
void red()
{
  analogWrite(REDPIN, 225);
  analogWrite(GREENPIN, 0);
  analogWrite(BLUEPIN, 0);
}

void blue()
{
  analogWrite(REDPIN, 0);
  analogWrite(GREENPIN, 0);
  analogWrite(BLUEPIN, 255);
}


