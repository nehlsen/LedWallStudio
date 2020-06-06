#include "FastLED.h"
#include "../../src/BitmapEditor.h"
#include <QtCore/QDebug>

CRGB::CRGB()
{}

CRGB::CRGB(Color color)
{
    m_color = toQColor(color);
}

CRGB::CRGB(int _r, int _g, int _b):
    r(_r), g(_g), b(_b)
{
    // FIXME member variables r, g and b are not used
    m_color.setRgb(_r, _g, _b);
}

CRGB & CRGB::operator=(Color color)
{
    m_color = toQColor(color);
    return *this;
}

CRGB & CRGB::operator+=(const CRGB &other)
{
    m_color.setRed(qMin(m_color.red() + other.m_color.red(), 255));
    m_color.setGreen(qMin(m_color.green() + other.m_color.green(), 255));
    m_color.setBlue(qMin(m_color.blue() + other.m_color.blue(), 255));

    return *this;
}

void CRGB::setHSV(quint8 h, quint8 s, quint8 v)
{
    m_color.setHsv(h, s, v);
}

CRGB & CRGB::nscale8(int scaledown)
{
    const double factor = qBound(0, scaledown, 256) / 256.0;
    m_color.setRedF(m_color.redF() * factor);
    m_color.setGreenF(m_color.greenF() * factor);
    m_color.setBlueF(m_color.blueF() * factor);

    return *this;
}

CRGB CRGB::lerp8(const CRGB &other, int frac) const
{
    CRGB newColor;
    newColor.m_color.setRed((m_color.red() + other.m_color.red()) / 2);
    newColor.m_color.setGreen((m_color.green() + other.m_color.green()) / 2);
    newColor.m_color.setBlue((m_color.blue() + other.m_color.blue()) / 2);

    return newColor;
}

QColor CRGB::getQColor() const
{
    if (!m_color.isValid()) {
        return Qt::black;
    }

    return m_color;
}

QColor CRGB::toQColor(Color color) const
{
    switch(color) {
        case Red: return Qt::red;
        case Green: return Qt::green;
        case Blue: return Qt::blue;
        case Black: return Qt::black;
        case White: return Qt::white;
    }

    return QColor();
}

CHSV::CHSV(quint8 h, quint8 s, quint8 v)
{
    setHSV(h, s, v);
}

/****************************************************************************************/

CLEDController::CLEDController()
{}

CLEDController::CLEDController(BitmapEditor *editor):
    m_editor(editor)
{}

CLEDController::CLEDController(BitmapEditor *editor, int size):
    m_editor(editor), m_leds(size)
{}

CRGB & CLEDController::operator[](int index)
{
//    if (index >= m_leds.size()) {
//        return CRGB();
//    }

    return m_leds[index];
}

int CLEDController::size() const
{
    return m_leds.size();
}

//CRGB * CLEDController::leds()
//{}

QVector<CRGB> & CLEDController::leds()
{
    return m_leds;
}

void CLEDController::show()
{
    if (m_editor == nullptr) {
        return;
    }

    Bitmap bitmap = Bitmap();
    for (int y = 0; y < m_editor->getSize().height(); ++y) {
        for (int x = 0; x < m_editor->getSize().width(); ++x) {
            const int index = x + y * m_editor->getSize().width();

            bitmap.insert({x, y}, (*this)[index].getQColor());
        }
    }

    m_editor->setBitmap(bitmap);
}

void CLEDController::showLeds(uint8_t brightness)
{
    show();
}

void CLEDController::showColor(const CRGB &data, uint8_t brightness)
{
    const int oldSize = size();
    m_leds.clear();
    m_leds.fill(data, oldSize);
    show();
}

void CLEDController::clearLedData()
{
    showColor(CRGB::Black);
}
