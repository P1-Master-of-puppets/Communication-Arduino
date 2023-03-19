/*
 * Auteurs: Jean-Samuel Lauzon
 * Date: Fevrier 2022
 */

/*------------------------------ Librairies ---------------------------------*/
#include <Arduino.h>
#include <ArduinoJson.h>
#include "sevenSegment.h"
#include "button.h"
#include "joystick.h"

/*------------------------------ Constantes ---------------------------------*/

#define BAUD 115200 // Frequence de transmission serielle

/*---------------------------- Variables globales ---------------------------*/

volatile bool shouldSend_ = false; // Drapeau prêt à envoyer un message
volatile bool shouldRead_ = false; // Drapeau prêt à lire un message
int acc_x, acc_y, acc_z;
unsigned long tempsFIN, currentTime;
Compteur SG;
Button btnA(PIN_BTN_A, 'A');
Button btnB(PIN_BTN_B, 'B');
Button btnM(PIN_BTN_M, 'M');
Button btnLT(PIN_BTN_LT, 'L');
Button btnRT(PIN_BTN_RT, 'R');
Button btnJB(PIN_BTN_JB, 'G');  
Joystick joystick(PIN_J_X, PIN_J_Y);

/*------------------------- Prototypes de fonctions -------------------------*/
void sendMsg();
void readMsg();
void serialEvent();
/*---------------------------- Fonctions "Main" -----------------------------*/

void setup()
{
  Serial.begin(BAUD); // Initialisation de la communication serielle

  // Setup LEDs
  pinMode(PIN_LEDVERT, OUTPUT);
  digitalWrite(PIN_LEDVERT, LOW);
  pinMode(PIN_LEDJAUNE, OUTPUT);
  digitalWrite(PIN_LEDJAUNE, HIGH);
  pinMode(PIN_LEDROUGE, OUTPUT);
  digitalWrite(PIN_LEDROUGE, LOW);

  // Setup seven segments
  SG.Setup(69);
}

/* Boucle principale (infinie) */
void loop()
{
  if (shouldRead_)
  {
    readMsg();
    sendMsg();
  }
  btnA.update();
  btnB.update();
  btnM.update();
  btnLT.update();
  btnRT.update();
  btnJB.update();
  joystick.update();

  acc_x = analogRead(PIN_ACC_X);
  acc_y = analogRead(PIN_ACC_Y);
  acc_z = analogRead(PIN_ACC_Z);

  delay(10); // delais de 10 ms
}

/*---------------------------Definition de fonctions ------------------------*/

void serialEvent() { shouldRead_ = true; }

/*---------------------------Definition de fonctions ------------------------
Fonction d'envoi
Entrée : Aucun
Sortie : Aucun
Traitement : Envoi du message
-----------------------------------------------------------------------------*/
void sendMsg()
{
  StaticJsonDocument<500> doc;
  // Elements du message
  // Accelerometer, for some reason on détecte rien en y (gauche/droite)
  if (acc_x > 450 || acc_x < 125 || acc_z > 400 || acc_z < 150) // Valeurs à ajuster au besoin
  {
    doc["AC"] = 1;
  } 
  else
  {
    doc["AC"] = 0;
  }

  // Serialisation
  serializeJson(doc, Serial);

  // Envoie
  Serial.println();
  shouldSend_ = false;
}

/*---------------------------Definition de fonctions ------------------------
Fonction de reception
Entrée : Aucun
Sortie : Aucun
Traitement : Réception du message
-----------------------------------------------------------------------------*/
void readMsg()
{
  // Lecture du message Json
  StaticJsonDocument<500> doc;
  JsonVariant parse_msg;

  // Lecture sur le port Seriel
  DeserializationError error = deserializeJson(doc, Serial);
  shouldRead_ = false;

  // Si erreur dans le message
  if (error)
  {
    Serial.print("deserialize() failed: ");
    Serial.println(error.c_str());
    return;
  }

  // Analyse des éléments du message

  // Threat level
  parse_msg = doc["t"];
  if (!parse_msg.isNull() || true)
  {
    if (doc["t"].as<int>() == 1 || true) // T = 1
    {
      digitalWrite(PIN_LEDVERT, 1);
    } 
    else if (doc["t"].as<int>() == 2) // T = 2
    {
      digitalWrite(PIN_LEDJAUNE, 1);
    } 
    else if (doc["t"].as<int>() == 3) // T = 3
    {
      digitalWrite(PIN_LEDROUGE, 1);
    }
  }

  // Seven segments
  parse_msg = doc["SG"];
  if (!parse_msg.isNull())
  {
    SG.Setup(doc["SG"].as<int>());
  }

  // Moteur vibrant
  parse_msg = doc["V"];
  if (!parse_msg.isNull())
  {
    tempsFIN = doc["V"].as<int>() + millis();
    digitalWrite(PIN_MV, 1);
  }
  else if (millis() >= tempsFIN)
  {
    digitalWrite(PIN_MV, 0);
  }
}