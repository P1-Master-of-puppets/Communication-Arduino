#ifndef JOYSTICK_H__
#define JOYSTICK_H__

#include <Arduino.h>
#include "joystickState.h"

#define J_MAX_X 1024
#define J_MAX_Y 1024
#define J_TAILLE_DEADZONE 50

class Joystick
{
private:
    int _pin_x;
    int _pin_y;
    JoystickState _lastState;
    const char _prefix = 'J';
public:
    Joystick(int pin_x, int pin_y);
    ~Joystick();
    void update();
};

#endif