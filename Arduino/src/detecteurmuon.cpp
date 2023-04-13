#include "detecteurmuon.h"

DetecteurMuon::DetecteurMuon(int pin, char prefix)
{
    _pin = pin;
    _prefix = prefix;
}

DetecteurMuon::~DetecteurMuon()
{
    
}

void DetecteurMuon::detection()
{
    delay(0.1);
    int valeur = pulseIn(_pin, HIGH);
    char* buffer = new char[2];
    buffer[0] = _prefix;
    if (valeur != 0) {
        i++;
        if (i == 7)
            i = 0;
        buffer[1] = _pieces[i];
        Serial.write(buffer, 2);
    }
    else {
        i++;
        if (i == 7)
            i = 0; 
    }
}