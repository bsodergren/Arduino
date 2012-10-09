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
  if(selectedMode < 5)
  {
    selectedMode++;
  }
  else {
    selectedMode=1;
  }
  Serial.println(selectedMode);

}

int delaySpeed()
{
  sensorValue = analogRead(sensorPin); 
  delayValue = map(sensorValue, 0, 1023, 20, 500); 
  //Serial.println(delayValue);

  return delayValue;
}

void rotate()
{

  red();
  delay(delaySpeed());
  blue(); 
  delay(delaySpeed());
  green();
  delay(delaySpeed());
}


void loop()
{

  switch (selectedMode)
  {
  case 1:
    red();
    break;

  case 2:
    blue();
    break;

  case 3:
    green();
    break;

  case 4:
    white();
    break;

  case 5:
    rotate();
    break;

  case 6:
    off();
    break;

  }
}


void white()
{
  shifter.clear();
  analogWrite(REDPIN, 255);
  analogWrite(GREENPIN, 255);
  analogWrite(BLUEPIN, 255);
  shifter.setAll(HIGH);
  shifter.write();
}  
void red()
{
  shifter.clear();
  analogWrite(REDPIN, 225);
  analogWrite(GREENPIN, 0);
  analogWrite(BLUEPIN, 0);
  shifter.setAll(HIGH);
  shifter.write();
}

void blue()
{
  shifter.clear();
  analogWrite(REDPIN, 0);
  analogWrite(GREENPIN, 0);
  analogWrite(BLUEPIN, 255);
  shifter.setAll(HIGH);
  shifter.write();
}

void green()
{
  shifter.clear();
  analogWrite(REDPIN, 0);
  analogWrite(GREENPIN, 255);
  analogWrite(BLUEPIN, 0);
  shifter.setAll(HIGH);
  shifter.write();
}

void off()
{
  shifter.clear();

  shifter.setAll(LOW);
  shifter.write();
}





