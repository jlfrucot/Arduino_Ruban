/* Une petite lib pour avoir un minuteur indiquant que le temps imparti est écoulé
  * @see 
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
#ifndef JLF_TIMER
#define JLF_TIMER

#include <Arduino.h>

class JLF_Timer
{

public:
  /*!
    Initialise un compteur de temps avec un delai en millisecondes
    @param delay : valeur en milisecondes après laquelle isTimeElapsed() renvoie true.
  */
  JLF_Timer(unsigned long delay);
  ~JLF_Timer();
  /*!
     @brief renvoie true si le delai est dépassé et relance le compteur
     @return true si le délai est dépassé
  */
  bool isTimeElapsed();

  /*! démarre le décompteur */
  inline void start() { restart(); }

  /*! réinitialise le decompteur avec le delai précédemment déclaré */
  void restart();

  /*! 
    @brief démarre le décompteur avec le delai passé en paramètre 
    @param delay le délai avant bascule en ms
  */
  inline void start(unsigned long delay) { restart(delay); }

  /*!
  @brief réinitialise le decompteur avec le nouveau delai passé en paramètre 
  @param le delai avant bascule en ms
  */
  void restart(unsigned long delay);

private:
  
  unsigned long m_previousTime; // temps au départ du compteur
  unsigned long m_delay;        // le delai
};

#endif