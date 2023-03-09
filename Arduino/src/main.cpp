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
#define J_MAX_X 10000
#define J_MAX_Y 10000
#define J_TAILLE_DEADZONE 1000

/*---------------------------- Variables globales ---------------------------*/

volatile bool shouldSend_ = false; // Drapeau prêt à envoyer un message
volatile bool shouldRead_ = false; // Drapeau prêt à lire un message
int btnA, btnB, btnM, btnLT, btnRT, btnJB, j_x, j_y;
unsigned long tempsFIN, currentTime;
Compteur SG;

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
  j_x = analogRead(PIN_J_X);
  j_y = analogRead(PIN_J_Y);
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
  // Direction du joystick
  if (j_x < (J_MAX_X/2 - J_TAILLE_DEADZONE/2) || j_x > (J_MAX_X/2 + J_TAILLE_DEADZONE/2))
  {
    if (j_y < (J_MAX_Y/2 - J_TAILLE_DEADZONE)/2 || j_y > (J_MAX_Y/2 + J_TAILLE_DEADZONE/2))
    {
      // Côté gauche
      if (j_x <= J_MAX_X/2 && j_y > -1 * j_x + J_MAX_Y)
      {
        doc["J"] = "U";
      }
      else if (j_x <= J_MAX_X/2 && j_y < j_x)
      {
        doc["J"] = "D";
      }
      else 
      {
        doc["J"] = "L";
      }
      // Côté droit
      if (j_x >= J_MAX_X/2 && j_y > j_x)
      {
        doc["J"] = "U";
      }
      else if (j_x >= J_MAX_X/2 && j_y < -1 * j_x + J_MAX_Y)
      {
        doc["J"] = "D";
      }
      else
      {
        doc["J"] = "R";
      }
    }
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
  parse_msg = doc["T"];
  if (!parse_msg.isNull())
  {
    if (doc["T"].as<int>() == 1) // T = 1
    {
      digitalWrite(PIN_LEDVERT, 1);
    } 
    else if (doc["T"].as<int>() == 2) // T = 2
    {
      digitalWrite(PIN_LEDJAUNE, 1);
    } 
    else if (doc["T"].as<int>() == 3) // T = 3
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