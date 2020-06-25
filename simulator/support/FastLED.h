#ifndef LEDWALLSTUDIO_SIMULATOR_SUPPORT_FASTLED_H
#define LEDWALLSTUDIO_SIMULATOR_SUPPORT_FASTLED_H

#include <QtCore/QVector>
#include "esp32-hal.h"
#include "colorutils.h"
#include "CRGB.h"
#include "CHSV.h"

class BitmapEditor;

// FIXME move classes to separate Files

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

    void clear(bool writeData = false);
    void delay(unsigned long ms) {}
};

static CFastLED FastLED;

#endif //LEDWALLSTUDIO_SIMULATOR_SUPPORT_FASTLED_H
