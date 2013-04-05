#include "StateButton.h"

StateButton::StateButton(int buttonPin, int buttonPinMode /*= INPUT*/)
{
	pin = buttonPin;
	lastState = buttonPinMode == INPUT_PULLUP ? HIGH : LOW;
	pushCount=0;
	setPressedValue(buttonPinMode == INPUT_PULLUP ? LOW : HIGH);
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
		if (reading == pressed) { //pressed
			++pushCount;
//#ifdef DEBUG
			Serial.print("Change state:");
			Serial.print(reading, DEC);
			Serial.print(", count:");
			Serial.print(pushCount, DEC);
			Serial.print(", change:");
			Serial.println(pushCount % 4, DEC);
		}
//#endif
	}
	lastState = reading;

	return (0 == pushCount % 2) ? pressed : !pressed; //change state
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
