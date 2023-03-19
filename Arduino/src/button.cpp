#include "button.h"

Button::Button(int pin, char prefix)
{
    _lastState = false;
    _pin = pin;
    _prefix = prefix;
}

Button::~Button()
{
    
}

void Button::update()
{
    bool state = digitalRead(_pin) == LOW;
    if (_lastState != state)
    {
        _lastState = state;
        char* buffer = new char[2];
        buffer[0] = _prefix;
        if (state)
            buffer[1] = '1';
        else
            buffer[1] = '0';
        Serial.print(buffer);
    }    
}