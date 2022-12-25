#include "esp32-hal.h"
#include <QtCore/QTime>
#include <QtCore/QRandomGenerator>

/** 1.000th of a second (1 milli = 0.001s) */
int millis()
{
    return QTime::currentTime().msecsSinceStartOfDay();
}

/** 1.000.000th of a second (1 = 0.000001s) */
int64_t esp_timer_get_time()
{
    return (int64_t)millis() * 1000;
}

int constrain(int val, int min, int max)
{
    return qBound(min, val, max);
}

int random8(int lim)
{
    return QRandomGenerator::global()->bounded(0, lim);
}

int random16(int lim)
{
    return QRandomGenerator::global()->bounded(0, lim);
}
