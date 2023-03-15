#include "sevenSegment.h"

Display::Display()
{
}

Display::~Display()
{
}

void Display::SetPins(int newA, int newB, int newC, int newD, int newE, int newF, int newG, int newDP)
{
	a = newA;
	b = newB;
	c = newC;
	d = newD;
	e = newE;
	f = newF;
	g = newG;
	
	pinMode(a, OUTPUT);
	pinMode(b, OUTPUT);
	pinMode(c, OUTPUT);
	pinMode(d, OUTPUT);
	pinMode(e, OUTPUT);
	pinMode(f, OUTPUT);
	pinMode(g, OUTPUT);
	pinMode(dp, OUTPUT);
}

void Display::AllOff()
{
	digitalWrite(a, HIGH);
	digitalWrite(b, HIGH);
	digitalWrite(c, HIGH);
	digitalWrite(d, HIGH);
	digitalWrite(e, HIGH);
	digitalWrite(f, HIGH);
	digitalWrite(g, HIGH);
	digitalWrite(dp, HIGH);
}

void Display::SetDP(bool etat)
{
	if (etat == true)
	{
		digitalWrite(dp, LOW);
	}

	if (etat == false)
	{
		digitalWrite(dp, false);
	}
}

void Display::Set(int number)
{
	AllOff();

	switch (number)
	{
	case 0:
		digitalWrite(a, LOW);
		digitalWrite(b, LOW);
		digitalWrite(c, LOW);
		digitalWrite(d, LOW);
		digitalWrite(e, LOW);
		digitalWrite(f, LOW);
		break;

	case 1:
		digitalWrite(b, LOW);
		digitalWrite(c, LOW);
		break;

	case 2:
		digitalWrite(a, LOW);
		digitalWrite(b, LOW);
		digitalWrite(g, LOW);
		digitalWrite(d, LOW);
		digitalWrite(e, LOW);
		break;

	case 3:
		digitalWrite(a, LOW);
		digitalWrite(b, LOW);
		digitalWrite(c, LOW);
		digitalWrite(d, LOW);
		digitalWrite(g, LOW);
		break;

	case 4:
		digitalWrite(b, LOW);
		digitalWrite(c, LOW);
		digitalWrite(g, LOW);
		digitalWrite(f, LOW);
		break;

	case 5:
		digitalWrite(a, LOW);
		digitalWrite(g, LOW);
		digitalWrite(c, LOW);
		digitalWrite(d, LOW);
		digitalWrite(f, LOW);
		break;

	case 6:
		digitalWrite(a, LOW);
		digitalWrite(g, LOW);
		digitalWrite(c, LOW);
		digitalWrite(d, LOW);
		digitalWrite(e, LOW);
		digitalWrite(f, LOW);
		break;

	case 7:
		digitalWrite(a, LOW);
		digitalWrite(b, LOW);
		digitalWrite(c, LOW);
		break;

	case 8:
		digitalWrite(a, LOW);
		digitalWrite(b, LOW);
		digitalWrite(c, LOW);
		digitalWrite(d, LOW);
		digitalWrite(e, LOW);
		digitalWrite(f, LOW);
		digitalWrite(g, LOW);
		break;

	case 9:
		digitalWrite(a, LOW);
		digitalWrite(b, LOW);
		digitalWrite(c, LOW);
		digitalWrite(d, LOW);
		digitalWrite(g, LOW);
		digitalWrite(f, LOW);
		break;
	}
}

Compteur::Compteur()
{
	Afficheur1.SetPins(PIN_SEG_1_1, PIN_SEG_1_2, PIN_SEG_1_3, PIN_SEG_1_4, PIN_SEG_1_5, PIN_SEG_1_6, PIN_SEG_1_7, 0);
	Afficheur2.SetPins(PIN_SEG_2_1, PIN_SEG_2_2, PIN_SEG_2_3, PIN_SEG_2_4, PIN_SEG_2_5, PIN_SEG_2_6, PIN_SEG_2_7, 0);
	dizaines = 0;
	unites = 0;
}

Compteur::~Compteur()
{
}

void Compteur::Add_1()
{
	increment = increment + 1;
	if (increment > 99)
	{
		increment = 99;
	}
	Setup(increment);
}

void Compteur::Remove_1()
{
	if (increment == 0)
	{
		Setup(increment);
		return;
	}
	increment = increment - 1;
	Setup(increment);
}

void Compteur::Reset()
{
	increment = 0;
	Setup(0);
}

void Compteur::Setup(int valeur)
{
	dizaines = valeur / 10;
	unites = valeur % 10;

	Afficheur1.Set(dizaines);
	Afficheur2.Set(unites);
}
