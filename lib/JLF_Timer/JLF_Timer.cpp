/* Projet ESP32_Sensor_Temp_V2
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
 
 #include "JLF_Timer.h"

JLF_Timer::JLF_Timer(unsigned long delay)
{
    m_delay = delay;
    m_previousTime = millis();
    //    m_timeElapsed=false;
}
JLF_Timer::~JLF_Timer()
{
}

bool JLF_Timer::isTimeElapsed()
{
    bool timeElapsed = false;
    if (millis() - m_previousTime >= m_delay)
    {
        timeElapsed = true;
        m_previousTime = millis();
    }
    return timeElapsed;
}
void JLF_Timer::restart()
{
    m_previousTime = millis();
}
void JLF_Timer::restart(unsigned long delay)
{
    m_delay = delay;
    restart();
}