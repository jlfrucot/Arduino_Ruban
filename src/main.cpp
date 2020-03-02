/* Projet Talisman
  * Une petite appli pour gérer un (des) ruban(s) de leds
  *
  * @author 2020 Jean-Louis Frucot <frucot.jeanlouis@free.fr>
  * @see The GNU Public License (GPL)
  *
  * this program is free software you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful, but
  * WITHOUT ANY WARRANTY, without even the implied warranty of MERCHANTABILITY
  * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
  * for more details.
  *
  * You should have received a copy of the GNU General Public License along
  * with this program. If not, see <http://www.gnu.org/licenses/>.
  */

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "JLF_Timer.h"
#include "ruban.h"
#define OUTPUT_SERIAL_PRINT 1 // 1 affiche les debugs, 0 ne les affiche pas
////////////////////////////////////////////// Déclaration des fonctions //

void start_01();
void stop_01();
////////////////////////////////////////////// LEDS NEOPIXELS ///////////

const uint8_t LEDSPIN = 6;                            // broche data pour le ruban de leds
const uint8_t CD_STRIPE_01 = 10;                      // broche reliée à l'ESP32 qui controle le ruban n°1
bool stripeState01 = false;                           // Etat de la broche CCD_STRIPE_01
const uint16_t LEDSCOUNT = 60;                        // nb de broches du ruban de leds
uint16_t m_stepDuration = 25;                         //ms règle la vitesse d'affichage des Leds
unsigned char m_color[3] = {255, 0, 0};               // r, g, b Couleur d'affichage des leds
unsigned char m_motif[] = {1, 4, 8, 16, 32, 64, 128}; // diviseur de luminosité pour les leds allumées
int8_t m_nbBoucle = -1;                               // Nombre de cycles d'affichage (-1 infini)
int8_t m_currentBoucle = m_nbBoucle;                  // Le numéro de la boucle courante
uint16_t m_currentLed = 0;                            // La première led du motif (à droite)

uint8_t m_adaptedColors[sizeof(m_motif)][3];
// Création d'un ruban de leds
Ruban *m_stripe = new Ruban(LEDSCOUNT, LEDSPIN, NEO_RGB + NEO_KHZ800);
// Création d'un timer pour rythmer l'affichage des leds
JLF_Timer *m_stripeTimer = new JLF_Timer(m_stepDuration); // ms

void setup()
{
  Serial.begin(9600);

  pinMode(CD_STRIPE_01, INPUT);
  // Initialisation du ruban
  m_stripe->begin(); // Obligatoire
  m_stripe->setColor(m_color[0], m_color[1], m_color[2]);
  m_stripe->setMotif(m_motif, sizeof(m_motif));
  m_stripe->clear();
  stop_01();
  m_stripe->show();

#if OUTPUT_SERIAL_PRINT
  Serial.println("Setup terminé");
#endif
delay(2000);
}

void loop()
{
  if(digitalRead(CD_STRIPE_01) != stripeState01)
  {
    stripeState01 = !stripeState01;
    if(stripeState01)
    {
      start_01();
    }
    else
    {
      stop_01();
    }
    
  }
  // ici, on gère l'affichage à chaque fois que le timer a basculé
  if (m_stripeTimer->isTimeElapsed())
  {
    // On gère le ruban m_stripe
    if (m_stripe->isStopped() == false) // on ne fait rien si le ruban est arrêté
    {
      if (m_nbBoucle == -1) // nombre de boucles infini
      {
        m_currentLed = m_stripe->nextStep();
#if OUTPUT_SERIAL_PRINT
        Serial.println("m_stripe : boucle infinie");
#endif
      }
      else
      {
        if (m_currentBoucle > 0) // Il reste des boucles à faire
        {
          m_currentLed = m_stripe->nextStep();
#if OUTPUT_SERIAL_PRINT
          Serial.print("Boucle n°");
          Serial.print(m_nbBoucle);
          Serial.print("   Led n°");
          Serial.println(m_currentLed);
#endif
          if (m_currentLed - LEDSCOUNT == 0) // A-t-on fini une boucle ?
          {
            m_currentBoucle--; // boucle suivante
          }
        }
        else // C'est la dernière boucle
        {
          if (m_currentLed == LEDSCOUNT) //On est arrivé à la fin du ruban
          {
            m_currentLed = m_stripe->stop();
#if OUTPUT_SERIAL_PRINT
            Serial.print("Plus de boucle");
            Serial.print("     Arrêté à la Led n°");
            Serial.println(m_currentLed);
            Serial.print("m_stripe stoppé ");
            Serial.println(m_stripe->isStopped());
#endif
          }
        }
      }
    }
  }

  // // Essai de couleurs aléatoires
  // if(m_stripe->isStopped() == true)
  // {
  //   delay(3000);
  //   int c1, c2, c3;
  //   m_nbBoucle = 1;
  //   do
  //   {
  //    c1 = random()%2 * 255;
  //    c2 = random()%2 * 255;
  //    c3 = random()%2 * 255;
  //   } while (c1+c2+c3 == 0);
    
  //   m_stripe->setColor(c1,c2,c3);
  //   start_01();
  // }
}

////////////////////////////////// Définition des fonctions //////////

void start_01()
{
  m_currentBoucle = m_nbBoucle;
  m_stripe->restart();
}

void stop_01()
{
  m_currentLed = m_stripe->stop();
}