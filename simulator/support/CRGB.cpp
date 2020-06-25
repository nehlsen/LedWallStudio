#include "CRGB.h"

CRGB::CRGB()
{}

CRGB::CRGB(Color color)
{
    m_color = toQColor(color);
    updateProperties();
}

CRGB::CRGB(quint8 _r, quint8 _g, quint8 _b):
    r(_r), g(_g), b(_b)
{
    m_color.setRgb(_r, _g, _b);
    updateProperties();
}

CRGB & CRGB::operator=(Color color)
{
    m_color = toQColor(color);
    updateProperties();
    return *this;
}

CRGB & CRGB::operator+=(const CRGB &other)
{
    m_color.setRed(qMin(m_color.red() + other.m_color.red(), 255));
    m_color.setGreen(qMin(m_color.green() + other.m_color.green(), 255));
    m_color.setBlue(qMin(m_color.blue() + other.m_color.blue(), 255));
    updateProperties();

    return *this;
}

void CRGB::setHSV(quint8 h, quint8 s, quint8 v)
{
    m_color.setHsv(h, s, v);
    updateProperties();
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
    newColor.updateProperties();

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

        case Yellow: return Qt::yellow;

        case Black: return Qt::black;
        case White: return Qt::white;
    }

    return QColor();
}

void CRGB::updateProperties()
{
    r = m_color.red();
    g = m_color.green();
    b = m_color.blue();
}
