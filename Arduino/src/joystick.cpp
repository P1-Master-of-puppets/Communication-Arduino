#include "joystick.h"

Joystick::Joystick(int pin_x, int pin_y)
{
    _lastState = JoystickState::Idle;
    _pin_x = pin_x;
    _pin_y = pin_y;
}

Joystick::~Joystick()
{
    
}

void Joystick::update()
{
    int j_x = analogRead(_pin_x);
    int j_y = analogRead(_pin_y);
    JoystickState state;
    if (!(j_x > (J_MAX_X/2 - J_TAILLE_DEADZONE/2) && j_x < (J_MAX_X/2 + J_TAILLE_DEADZONE/2) && j_y > (J_MAX_Y/2 - J_TAILLE_DEADZONE/2) && j_y < (J_MAX_Y/2 + J_TAILLE_DEADZONE/2)))
    {
        // Côté gauche
        if (j_x >= J_MAX_X/2 && j_y > j_x)
            state = JoystickState::Up;
        else if (j_x >= J_MAX_X/2 && j_y < -1 * j_x + J_MAX_Y)
            state = JoystickState::Down;
        else if (j_x >= J_MAX_X/2)
            state = JoystickState::Left;
        // Côté droit
        if (j_x <= J_MAX_X/2 && j_y > -1 * j_x + J_MAX_Y)
            state = JoystickState::Up;
        else if (j_x <= J_MAX_X/2 && j_y < j_x)
            state = JoystickState::Down;
        else if (j_x <= J_MAX_X/2)
            state = JoystickState::Right;
    }
    else
        state = JoystickState::Idle;
    if (_lastState != state)
    {
        _lastState = state;
        char* buffer = new char[2];
        buffer[0] = _prefix;
        if (state == JoystickState::Idle)
            buffer[1] = 'I';
        else if (state == JoystickState::Up)
            buffer[1] = 'U';
        else if (state == JoystickState::Down)
            buffer[1] = 'D';
        else if (state == JoystickState::Right)
            buffer[1] = 'R';
        else if (state == JoystickState::Left)
            buffer[1] = 'L';
        Serial.write(buffer);
    }    
}