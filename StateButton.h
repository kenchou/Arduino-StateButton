#ifndef StateButton_h
#define StateButton_h

#include "Arduino.h"

class StateButton
{
	protected:
		int pin;
		int state;
		int lastState;
		int pressed;
		int pushCount;
		long lastDebounceTime;  // the last time the output pin was toggled
		long debounceDelay;
		bool _isPressed();
	public:
		StateButton(int buttonPin, int buttonPinMode = INPUT);
		void setPressedValue(int value = HIGH);
		void setDebounce(bool debounce);
		void setInitialState(int value);
		int readState();
		
		bool isPressed();
		bool isReleased();
		
		
};

#endif
