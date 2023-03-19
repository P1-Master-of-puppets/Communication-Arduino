#include <Arduino.h>
#include <ArduinoJson.h>
#include "sevenSegment.h"
#include "button.h"
#include "joystick.h"
#include "accelerometer.h"
#include <string.h>

#define BAUD 115200

Compteur SG;
Button btnA(PIN_BTN_A, 'A');
Button btnB(PIN_BTN_B, 'B');
Button btnM(PIN_BTN_M, 'M');
Button btnLT(PIN_BTN_LT, 'L');
Button btnRT(PIN_BTN_RT, 'R');
Button btnJB(PIN_BTN_JB, 'G');  
Joystick joystick(PIN_J_X, PIN_J_Y);
Accelerometer accelerometer(PIN_ACC_X, PIN_ACC_Y, PIN_ACC_Z, 'Y');
unsigned long tempsFIN; // pour le moteur vibrant

void updateControllerValues(char input[]){

  switch (input[0])
  {
  case 'S': // 7 Segment
    int nombre = (int)input[1]; 
    SG.Setup(nombre -1);
    break;
  case 'T': // Threat Level
    int nombre = (int)input[1];
    if (nombre = 1) 
    {
      digitalWrite(PIN_LEDVERT, LOW);
      digitalWrite(PIN_LEDJAUNE, HIGH);
      digitalWrite(PIN_LEDROUGE, HIGH);
    }
    if (nombre = 2) 
    {
      digitalWrite(PIN_LEDJAUNE, LOW);
      digitalWrite(PIN_LEDROUGE, HIGH);
    }
    if (nombre = 3) digitalWrite(PIN_LEDROUGE, LOW);
  case 'V': // Moteur Vibrant
    int nombre = (int)input[1];
    tempsFIN = nombre + millis();
    digitalWrite(PIN_MV, 1);
    break;
  default:
    break;
  }
}

char dest[128];
void readData(){
  char* caracter = new char[2];
  caracter[1] = '\0';
  while (Serial.available() > 0) {
    caracter[0] = (char)Serial.read();
    strcat(dest, caracter);
  }
  delete[] caracter;
}

void receiveData(){
  readData();
	if (strlen(dest) >= 3)
    return;

	//Make sure we only send 2 char at a time. Otherwise we might skip data and it will become extra weird
  int len = strlen(dest);
	if (len >= 2)
	{
		char inputs[2];
		inputs[0] = dest[0];
		inputs[1] = dest[1];
    //We remove 3 caracters because the last one is an end of line caracter
    memmove(dest, dest + 3, len);
		updateControllerValues(inputs);
	}
}

void setup()
{
  Serial.begin(BAUD); // Initialisation de la communication serielle

  // Setup LEDs
  pinMode(PIN_LEDVERT, OUTPUT);
  digitalWrite(PIN_LEDVERT, HIGH);
  pinMode(PIN_LEDJAUNE, OUTPUT);
  digitalWrite(PIN_LEDJAUNE, HIGH);
  pinMode(PIN_LEDROUGE, OUTPUT);
  digitalWrite(PIN_LEDROUGE, HIGH);

  // Setup seven segments
  SG.Setup(0);
}

/* Boucle principale (infinie) */
void loop()
{
  btnA.update();
  btnB.update();
  btnM.update();
  btnLT.update();
  btnRT.update();
  btnJB.update();
  joystick.update();
  accelerometer.update();
  receiveData();
  if (millis() >= tempsFIN)
    digitalWrite(PIN_MV, 0);
}

