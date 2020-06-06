#ifndef LEDWALLSTUDIO_SIMULATOR_SUPPORT_FASTLED_H
#define LEDWALLSTUDIO_SIMULATOR_SUPPORT_FASTLED_H

#include <QtCore/QVector>
#include <QtGui/QColor>
#include "esp32-hal.h"

class BitmapEditor;

// FIXME move classes to separate Files

class CRGB
{
public:
    enum Color {
        Red,
        Green,
        Blue,
        Black,
        White,
    };

    int r = 0;
    int g = 0;
    int b = 0;

    CRGB();
    CRGB(Color color);
    CRGB(int r, int g, int b);

    CRGB &operator=(Color color);
    CRGB &operator+=(const CRGB &other);

    void setHSV(quint8 h, quint8 s, quint8 v);

    CRGB &nscale8(int scaledown);
    CRGB lerp8(const CRGB& other, int frac) const; // FIXME does not the same thing as the original FastLED implementation

    QColor getQColor() const;

protected:
    QColor toQColor(Color color) const;

    QColor m_color;
};

class CHSV : public CRGB
{
public:
    CHSV(quint8 h, quint8 s, quint8 v);
};

class CLEDController
{
public:
    CLEDController();
    explicit CLEDController(BitmapEditor *editor);
    explicit CLEDController(BitmapEditor *editor, int size);

    CRGB& operator[](int index);

    int size() const;
//    CRGB *leds();
    QVector<CRGB> &leds();

    void show();
    void showLeds(uint8_t brightness = 255);
    void showColor(const CRGB &data, uint8_t brightness = 255);
    void clearLedData();

protected:
    BitmapEditor *m_editor = nullptr;
    QVector<CRGB> m_leds;
};

class CFastLED : public CLEDController
{
public:
    using CLEDController::CLEDController;

    void setBrightness(uint8_t scale) {}
    uint8_t getBrightness() { return 0xff; }

    void clear(bool writeData = false) {}
    void delay(unsigned long ms) {}
};

static CFastLED FastLED;

#endif //LEDWALLSTUDIO_SIMULATOR_SUPPORT_FASTLED_H
