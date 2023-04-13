#include "accelerometer.h"

Accelerometer::Accelerometer(int pin_x, int pin_y, int pin_z, char prefix)
{
    _pin_x = pin_x;
    _pin_y = pin_y;
    _pin_z = pin_z;
    _prefix = prefix;
}

Accelerometer::~Accelerometer()
{
    
}

void Accelerometer::update()
{
    int acc_x = analogRead(_pin_x);
    //int acc_y = analogRead(_pin_y);
    int acc_z = analogRead(_pin_z);
    bool state = 0;
    // For some reason on détecte rien en y (gauche/droite)
    if (acc_x > ACC_MAX_X || acc_x < ACC_MIN_X || acc_z > ACC_MAX_Z || acc_z < ACC_MIN_Z) // Valeurs à ajuster au besoin
        state = 1;

    if (state && millis() - _lastUpdate > 200)
    {
        _lastUpdate = millis();
        char* buffer = new char[2];
        buffer[0] = _prefix;
        buffer[1] = '1';
        
        Serial.write(buffer,2);
        delete[] buffer;
    }    
}