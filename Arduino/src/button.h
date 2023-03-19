#ifndef BUTTON_H__
#define BUTTON_H__

#include <Arduino.h>

class Button
{
private:
    int _pin;
    char _prefix;
    bool _lastState;
public:
    Button(int pin, char prefix);
    ~Button();
    void update();
};

#endif // BUTTON_H__