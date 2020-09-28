#ifndef LEDWALLSTUDIO_CRGB_H
#define LEDWALLSTUDIO_CRGB_H

#include <QtGui/QColor>

class CRGB
{
public:
    enum Color {
        Red,
        Green,
        Blue,

        Yellow,

        Black,
        White,
    };

    int r = 0;
    int g = 0;
    int b = 0;

    CRGB();
    CRGB(Color color);
    CRGB(quint8 r, quint8 g, quint8 b);
    CRGB(quint32 colorCode);

    CRGB &operator=(Color color);
    CRGB &operator+=(const CRGB &other);
    bool operator==(const CRGB &other) const;

    void setHSV(quint8 h, quint8 s, quint8 v);
    void setRGB(quint8 r, quint8 g, quint8 b);

    CRGB &nscale8(int scaledown);
    CRGB lerp8(const CRGB& other, int frac) const; // FIXME does not the same thing as the original FastLED implementation

    QColor getQColor() const;

protected:
    QColor toQColor(Color color) const;

    QColor m_color;
    // call after changes to m_color, updates properties: r, g and b
    void updateProperties();
};

#endif //LEDWALLSTUDIO_CRGB_H
