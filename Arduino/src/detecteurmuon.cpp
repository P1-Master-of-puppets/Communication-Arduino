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
    char* buffer = new char[2];
    buffer[0] = _prefix;
    if (valeur != 0) {
        i++;
        Serial.print(i);
        if (i == 8)
            i = 1;
        char p = _pieces[i];
        buffer[1] = p;
        Serial.write(buffer, 2);
    }
    else {
        i++;
        if (i == 8)
            i = 1; 
    }
}