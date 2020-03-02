/* Projet Talisman
  *Une petite lib pour gérer un ruban de leds
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

#ifndef RUBAN
#define RUBAN

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
/*!
Cette classe gère le défilement de leds NeoPixels. Une seule couleur à la fois. 
Un motif de luminosité peut être appliqué, c'est un tableau de diviseurs de la luminosité des leds.
la taille du tableau détermine le nombre de leds allumées(max 32)
*/
class Ruban
{
public:
/*!
  @brief Constructeur du ruban de leds
  @param ledsCount le nombre de leds du ruban
  @param pin la broche à laquelle est connectée le cable "data" du ruban
  @param type le type NeoPixel du ruban
*/
  Ruban(uint16_t ledsCount, uint8_t pin, neoPixelType type);
  ~Ruban();
/*!
  @brief Un motif détermine le nombre de leds allumée et leur brillance en terme de diviseur de la brillance de la couleur.
  (limité à 32 valeurs)
  @param motif[] un tableau de diviseurs de la luminosité, le nombre de valeur détermine le nombre de leds allumées
  @param size la taille du tableau (le nombre de leds allumées)
*/
  void setMotif(unsigned char motif[], uint8_t size = 0);
  /*!
  @brief Determine la couleur des leds (une seule couleur globale)
  @param r composante rouge de la couleur (0-255)
  @param g composante verte de la couleur (0-255)
  @param b composante bleue de la couleur (0-255)
  */
  void setColor(uint8_t r, uint8_t g, uint8_t b);
  /*!
    @brief initialise le ruban (un appel est obligatoire)
  */
  void begin();
  /*!
    @brief actualise les leds du ruban
  */
  void show();
  /*!
    @brief éteint toutes les leds du ruban
  */
  void clear();
  /*!
    @brief Fais avancer l'affichage des leds d'un pas
    @return la première led allumée du ruban
  */
  uint16_t nextStep();
  /*!
    @brief Reprend l'affichage du ruban à la première led (zéro)
  */
  void restart();
  /*!
    @brief Arrête le défilement des leds
    @return le numéro de la led à partir de laquelle le défilement a été arrêté
  */
  uint16_t stop();
  /*!
    @brief Return true si le défilement continue, ou false s'il est arrêté
  */
  bool isStopped();
  /*!
    @brief retourne un pointeur vers l'object NeoPixel créé dans le constructeur (le ruban de leds)
  */
  Adafruit_NeoPixel getNeoPixelsStripe();

private:
  /*!
  @brief remplit le tableau m_updatedColors avec les valeurs des composantes de couleur
  pour chaque valeur du motif (division de chaque composante par valeur du motif)
*/
  void updateColors();
  
  // variables internes

  Adafruit_NeoPixel *m_pixels; // Le ruban NeoPixels
  uint8_t m_pin;               // broche sur laquelle le ruban est attaché.
  uint16_t m_numPixels;        // nombre de pixels utilisables
  uint8_t m_motif[32] = {1, 4, 32, 64, 128}; // Le motif est un tableau de valeurs de luminosité des leds du motif.
  uint8_t m_sizeMotif = 5;
  uint16_t m_currentStep; // n° du pas dans la boucle : de 0 à (m_numpixels + m_sizeMotif -1)
  uint8_t m_color[3] = {128, 128, 128};

  bool m_stopped = false; // Statut du ruban arrêt ou défilement
  uint8_t m_updatedColors[32][3]; // Les valeurs de composante de couleur divisées par la valeur du motif
};

#endif