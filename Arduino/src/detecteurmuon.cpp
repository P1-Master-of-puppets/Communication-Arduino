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
    int valeur = analogRead(_pin);
    if (valeur != 0) {
        char* buffer = new char[2];
        buffer[0] = _prefix;
        i++;
        if (i == 7)
            i = 0;
        buffer[1] = _pieces[i];
        Serial.write(buffer, 2);
        delete[] buffer;
    }
    else {
        i++;
        if (i == 7)
            i = 0; 
    }
}