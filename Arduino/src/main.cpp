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
int btnA, btnB, btnM, btnLT, btnRT, btnJB;

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
  btnA = digitalRead(PIN_BTN_A);
  btnB = digitalRead(PIN_BTN_B);
  btnM = digitalRead(PIN_BTN_M);
  btnRT = digitalRead(PIN_BTN_RT);
  btnLT = digitalRead(PIN_BTN_LT);
  btnJB = digitalRead(PIN_BTN_JB);
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
  doc["A"] = btnA;
  doc["B"] = btnB;
  doc["M"] = btnM;
  doc["RT"] = btnRT;
  doc["LT"] = btnLT;
  doc["JB"] = btnJB;

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
      digitalWrite(PIN_LEDVERT, 1);
    } 
    else if (doc["T"].as<int>() == 2) // T = 2
    {
      digitalWrite(PIN_LEDVERT, 1);
      digitalWrite(PIN_LEDJAUNE, 1);
    } 
    else if (doc["T"].as<int>() == 3) // T = 3
    {
      digitalWrite(PIN_LEDVERT, 1);
      digitalWrite(PIN_LEDJAUNE, 1);
      digitalWrite(PIN_LEDROUGE, 1);
    }
  }

  // Seven segments
  parse_msg = doc["SG"];
  if (!parse_msg.isNull())
  {
    Compteur SG;
    SG.Setup(doc["SG"].as<int>());
  }

  // Moteur vibrant Comment le faire vibrer pour un certain temps?
  /*
  parse_msg = doc["V"];
  if (!parse_msg.isNull())
  {
    int tempsON = doc["V"].as<int>();
    int tempsFIN = millis() + tempsON;
  }
  */
}