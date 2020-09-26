#include "esp_log.h"
#include <cstdarg>
#include <QtCore/QString>
#include <QtCore/QDebug>
#include <QtCore/QTime>

void esp_fake_log_to_qdebug(const char* tag, const char* format, va_list args)
{
    qDebug().noquote().nospace()
            << QTime::currentTime().toString(Qt::ISODateWithMs)
            << QString("  %1  ").arg(QString(tag), -20, ' ')
            << QString::asprintf(format, args);
}

void esp_fake_log(const char* tag, const char* format, ...)
{
    va_list list;
    va_start(list, format);
    esp_fake_log_to_qdebug(tag, format, list);
    va_end(list);
}
