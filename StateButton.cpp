#include "StateButton.h"

StateButton::StateButton(int buttonPin, int buttonPinMode /*= INPUT*/)
{
	pin = buttonPin;
	lastState = buttonPinMode == INPUT_PULLUP ? HIGH : LOW;
	pushCount=0;
	setPressedValue();
	pinMode(buttonPin, buttonPinMode);
}

/**
 * set a state value as pressd state
 */
void StateButton::setPressedValue(int value /*= HIGH*/)
{
	pressed = value;
}

/**
 * set Initial state
 */
void StateButton::setInitialState(int value)
{
	lastState = value;
}

/**
 * @return int HIGH|LOW
 */
int StateButton::readState()
{
	int reading = digitalRead(pin);
	if (reading != lastState) {  //state changed
		lastDebounceTime = millis();
		
		//debounce
		if ((millis() - lastDebounceTime) > debounceDelay) {
			// whatever the reading is at, it's been there for longer
			// than the debounce delay, so take it as the actual current state:
			++pushCount;
			lastState = reading;
//#ifdef DEBUG
			Serial.print("Change state:");
			Serial.print(reading, DEC);
			Serial.print(", count:");
			Serial.print(pushCount, DEC);
			Serial.print(", change:");
			Serial.println(pushCount % 4, DEC);
//#endif
		}
	}

	return (0 == pushCount % 4) ? pressed : !pressed; //change state
}

bool StateButton::isPressed()
{
	return (readState() == pressed);
}

bool StateButton::isReleased()
{
	return !(readState() == pressed);
}

bool StateButton::_isPressed()
{
	return state == pressed;
}
