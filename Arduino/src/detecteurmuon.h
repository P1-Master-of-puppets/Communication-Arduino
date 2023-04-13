#ifndef DETECTEURMUON_H__
#define DETECTEURMUON_H__

#include <Arduino.h>

class DetecteurMuon
{
private:
    int _pin;
    char _prefix;
    char _pieces[7] = {'1', '2', '3', '4', '5', '6', '7'};
    int i = 0;
public:
    DetecteurMuon(int pin, char prefix);
    ~DetecteurMuon();
    void detection();
};

#endif // DETECTEURMUON_H__