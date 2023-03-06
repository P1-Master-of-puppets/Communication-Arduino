/*
 * Auteurs: Jean-Samuel Lauzon
 * Date: Fevrier 2022
 */

/*------------------------------ Librairies ---------------------------------*/
#include <Arduino.h>
#include <ArduinoJson.h>
#include <sevenSegment.h>

/*------------------------------ Constantes ---------------------------------*/

#define BAUD 115200 // Frequence de transmission serielle

/*---------------------------- Variables globales ---------------------------*/

volatile bool shouldSend_ = false; // Drapeau prêt à envoyer un message
volatile bool shouldRead_ = false; // Drapeau prêt à lire un message

int pinLEDvert = 1;
int pinLEDjaune = 2;
int pinLEDrouge = 3;

/*------------------------- Prototypes de fonctions -------------------------*/
void sendMsg();
void readMsg();
void serialEvent();
/*---------------------------- Fonctions "Main" -----------------------------*/

void setup()
{
  Serial.begin(BAUD); // Initialisation de la communication serielle
  // pinMode(pinLED, OUTPUT);
  // digitalWrite(pinLED, ledState);
}

/* Boucle principale (infinie) */
void loop()
{

  if (shouldRead_)
  {
    readMsg();
    sendMsg();
  }

  // potValue = analogRead(pinPOT);
  // Serial.println(potValue);          // debug
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
  // doc["time"] = millis();
  // doc["analog"] = potValue;

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

  // Analyse des éléments du message message

  // Threat level
  parse_msg = doc["T"];
  if (!parse_msg.isNull())
  {
    if (doc["T"].as<int>() == 1) // T = 1
    {
      digitalWrite(pinLEDvert, 1);
    } 
    else if (doc["T"].as<int>() == 2) // T = 2
    {
      digitalWrite(pinLEDvert, 1);
      digitalWrite(pinLEDjaune, 1);
    } 
    else if (doc["T"].as<int>() == 3) // T = 3
    {
      digitalWrite(pinLEDvert, 1);
      digitalWrite(pinLEDjaune, 1);
      digitalWrite(pinLEDrouge, 1);
    }
  }
}