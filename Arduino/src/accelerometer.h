#ifndef ACCELEROMETER_H__
#define ACCELEROMETER_H__

#include <Arduino.h>

#define ACC_MAX_X 450
#define ACC_MIN_X 125
#define ACC_MAX_Z 400
#define ACC_MIN_Z 150

class Accelerometer
{
private:
    int _pin_x;
    int _pin_y;
    int _pin_z;
    char _prefix;
    bool _lastState;
public:
    Accelerometer(int pin_x, int pin_y, int pin_z, char prefix);
    ~Accelerometer();
    void update();
};

#endif // ACCELEROMETER_H__