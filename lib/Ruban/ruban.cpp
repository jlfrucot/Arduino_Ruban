

#include "ruban.h"
#define OUTPUT_SERIAL_PRINT 0 // 0 pas de sortie sur le moniteur série, 1 sortie sur le moniteur série

Ruban::Ruban(uint16_t ledsCount, uint8_t pin, neoPixelType type)

{
    m_pixels = new Adafruit_NeoPixel(ledsCount, pin, type);
    m_currentStep = 0;
    m_numPixels = ledsCount;
    // m_pixels->begin();
    updateColors(); // Valeurs par défaut
}

Ruban::~Ruban()
{
}
void Ruban::begin()
{
    m_pixels->begin();
    m_pixels->show();
}

void Ruban::setMotif(unsigned char motif[], uint8_t size)
{
    if (size > 32)
    {
        size = 32;
    } // limite arbitraire
    m_sizeMotif = size;
    // Copie du tableau
    for (int i = 0; i < m_sizeMotif; i++)
    {
        m_motif[i] = motif[i];
    }
    updateColors();
}

void Ruban::setColor(uint8_t r, uint8_t g, uint8_t b)
{
// m_colors = m_pixels->Color(r, g, b);
#if OUTPUT_SERIAL_PRINT
    Serial.println("Setcolor");
#endif
    m_color[0] = r;
    m_color[1] = g;
    m_color[2] = b;
    updateColors();
}
void Ruban::show()
{
    m_pixels->show();
}

void Ruban::clear()
{
    m_pixels->clear();
}

void Ruban::restart()
{
    m_currentStep = 0;
    m_stopped = false;
}

uint16_t Ruban::stop()
{
    m_stopped = true;
    return m_currentStep;
}
bool Ruban::isStopped()
{
    return m_stopped;
}
uint16_t Ruban::nextStep()
{
    if (m_stopped == false) //
    {
        m_pixels->clear();

        for (uint8_t m = 0; m < m_sizeMotif; m++)
        {
            m_pixels->setPixelColor(m_currentStep - m, m_pixels->Color(m_updatedColors[m][0], m_updatedColors[m][1], m_updatedColors[m][2]));
        }
        m_pixels->show();
        m_currentStep = (m_currentStep + 1) % (m_numPixels + m_sizeMotif);
    }
    return m_currentStep;
}

Adafruit_NeoPixel Ruban::getNeoPixelsStripe()
{
    return *m_pixels;
}

void Ruban::updateColors()
{
    for (int8_t i = 0; i < m_sizeMotif; i++)
    {
        for (int8_t j = 0; j < 3; j++)
        {
            // On divise la valeur des composante de couleur par le nombre
            // fourni par le motif
            m_updatedColors[i][j] = m_color[j] / m_motif[i];
        }
    }
}