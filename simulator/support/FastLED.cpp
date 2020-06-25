#include "FastLED.h"
#include <BitmapEditor/BitmapEditor.h>
#include <QtCore/QDebug>

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

void CFastLED::clear(bool writeData)
{
    clearLedData();
}
