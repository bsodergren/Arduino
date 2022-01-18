/*
  MyDebounce - v1.2 - May 12, 2021.
  MIT Licensed.
  https://github.com/wkoch/MyDebounce

  Arduino library for button debouncing.
  Clearly based on the debounce example from the site: http://arduino.cc/en/Tutorial/MyDebounce
  
  Created by William Koch, improved by the community.
*/

class MyDebounce
{
public:
  // Debounces an input with a 50ms debounce by default.
  // Optional parameters:
  //    - Adjust the delay in milliseconds.
  //    - Pull-Up input.
  // Button pin is required.
  MyDebounce(byte button, unsigned long delay = 50, boolean pullup = true);
 void setCount(unsigned int _number);
  byte read();          // returns the debounced button state: LOW or HIGH.
 
   
  unsigned int count(); // Returns the number of times the button was pressed.
  void resetCount();    // Resets the button count number.

private:
  byte _button, _state, _lastState, _reading;
  unsigned int _count;
  unsigned long _delay, _last;
  boolean _wait;
  boolean _invert;
};

// Debounces an input with a 50ms debounce by default.
// Optional parameters:
//    - Adjust the delay in milliseconds.
//    - Pull-Up input.
MyDebounce::MyDebounce(byte button, unsigned long delay, boolean pullup)
{
  _invert = false;
  if (pullup)
  {
    pinMode(button, INPUT_PULLUP);
    _invert = true;
  }
  
  _button = button;
  _delay = delay;
  _state = _lastState = _reading = (_invert ? !digitalRead(_button) : digitalRead(_button));
  _last = millis();
  _count = 0;
}

// returns the debounced button state: LOW or HIGH.
byte MyDebounce::read()
{

  _reading = (_invert ? !digitalRead(_button) : digitalRead(_button)); // get current button state.
  if (_reading != _lastState)
  {                   // detect edge: current vs last state:
    _last = millis(); // store millis if change was detected.
    _wait = true;     // Just to avoid calling millis() unnecessarily.
  }

  if (_wait && (millis() - _last) > _delay)
  { // after the delay has passed:
    if (_reading != _state)
    {                    // if the change wasn't stored yet:
      _count++;          // Stores each change.
      _state = _reading; // store the button state change.
      _wait = false;
    }
  }
  _lastState = _reading;
  return _state;
}

// Returns the number of times the button was pressed.
unsigned int MyDebounce::count()
{
  MyDebounce::read();
  return _count / 2; // Counts only a full press + release.
}

// Resets the button count number.
void MyDebounce::setCount(unsigned int _number)
{
  _count = _number*2;
  return;
}

// Resets the button count number.
void MyDebounce::resetCount()
{
  _count = 0;
  return;
}
