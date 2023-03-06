#include <iostream>
#include <string>
#include <cmath>

using namespace std;

#include "7Segments.h"

Display::Display()
{

}

Display::~Display()
{

}

void Display::SetPins(int a, int b, int c, int d, int e, int f, int g, int dp)
{
	pinMode(a, OUTPUT);
	pinMode(b, OUTPUT);
	pinMode(c, OUTPUT);
	pinMode(d, OUTPUT);
	pinMode(e, OUTPUT);
	pinMode(f, OUTPUT);
	pinMode(g, OUTPUT);
	pinMode(dp, OUTPUT);
	return;
}

void Display::AllOff()
{
	digitalWrite(a, LOW);
	digitalWrite(b, LOW);
	digitalWrite(c, LOW);
	digitalWrite(d, LOW);
	digitalWrite(e, LOW);
	digitalWrite(f, LOW);
	digitalWrite(g, LOW);
	digitalWrite(dp, LOW);
	return;
}

void Display::SetDP(bool etat)
{
	if(etat == true)
	{
		digitalWrite(dp, HIGH);
	}
	
	if(etat == false)
	{
		digitalWrite(dp, false);
	}
	return;
}

void Display::Set(int number)
{	
	AllOff();
	
	switch(number)
	{
		case 0:
			digitalWrite(a, HIGH);
			digitalWrite(b, HIGH);
			digitalWrite(c, HIGH);
			digitalWrite(d, HIGH);
			digitalWrite(e, HIGH);
			digitalWrite(f, HIGH);
			break;

		case 1:
			digitalWrite(b, HIGH);
			digitalWrite(c, HIGH);
			break;

		case 2:
			digitalWrite(a, HIGH);
			digitalWrite(b, HIGH);
			digitalWrite(g, HIGH);
			digitalWrite(d, HIGH);
			digitalWrite(e, HIGH);
			break;
			
		case 3:
			digitalWrite(a, HIGH);
			digitalWrite(b, HIGH);
			digitalWrite(c, HIGH);
			digitalWrite(d, HIGH);
			digitalWrite(g, HIGH);
			break;
			
		case 4:
			digitalWrite(b, HIGH);
			digitalWrite(c, HIGH);
			digitalWrite(g, HIGH);
			digitalWrite(f, HIGH);
			break;
			
		case 5:
			digitalWrite(a, HIGH);
			digitalWrite(g, HIGH);
			digitalWrite(c, HIGH);
			digitalWrite(d, HIGH);
			digitalWrite(f, HIGH);
			break;
			
		case 6:
			digitalWrite(a, HIGH);
			digitalWrite(g, HIGH);
			digitalWrite(c, HIGH);
			digitalWrite(d, HIGH);
			digitalWrite(e, HIGH);
			digitalWrite(f, HIGH);
			break;
			
		case 7:
			digitalWrite(a, HIGH);
			digitalWrite(b, HIGH);
			digitalWrite(c, HIGH);
			break;
			
		case 8:
			digitalWrite(a, HIGH);
			digitalWrite(b, HIGH);
			digitalWrite(c, HIGH);
			digitalWrite(d, HIGH);
			digitalWrite(e, HIGH);
			digitalWrite(f, HIGH);
			digitalWrite(g, HIGH);
			break;
			
		case 9:
			digitalWrite(a, HIGH);
			digitalWrite(b, HIGH);
			digitalWrite(c, HIGH);
			digitalWrite(d, HIGH);
			digitalWrite(g, HIGH);
			digitalWrite(f, HIGH);
			break;
	}
	return;
}

Compteur::Compteur()
{
	Afficheur1.SetPins(int a, int b, int c, int d, int e, int f, int g, int dp);
	Afficheur2.SetPins(int a, int b, int c, int d, int e, int f, int g, int dp);
	dizaines = 0;
	unites = 0;
}

Compteur::~Compteur()
{

}

void Compteur::Add_1()
{
	increment = increment + 1;
	if(increment > 99)
	{
		increment = 99;
	}
	Setup(increment);
}

void Compteur::Remove_1()
{
	if(increment == 0)
	{	
		Setup(increment);
		return;
	}
	increment = increment - 1;
	Setup(increment);
	return;
}

void Compteur::Reset()
{
	increment = 0
	Setup(0);
}

void Compteur::Setup(int valeur)
{	
	dizaines = floor(valeur/10);
	unites = valeur % 10;
	
	Afficheur1.Set(dizaines);
	Afficheur2.Set(unites);
}




