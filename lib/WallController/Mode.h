#ifndef LEDWALLSTUDIO_MODE_H
#define LEDWALLSTUDIO_MODE_H

#include <QtCore/QList>
#include <QtCore/QJsonDocument>
#include <QtCore/QMap>
#include <QtCore/QVariant>

namespace LedWallStudio
{

class ModeOptions : public QMap<QString, QVariant>
{
public:
    static ModeOptions fromJson(const QJsonObject &jsonObject);
    void readJson(const QJsonObject &jsonObject);
    QJsonObject toJson() const;
};

struct Mode
{
    static Mode fromJson(const QJsonObject &jsonObject);

    bool isValid() const;

    qint8 Index;
    QString Name;
    ModeOptions Options;
};

class ModeList : public QList<Mode>
{
public:
    static ModeList fromJson(const QJsonDocument &jsonDocument);
};

} // namespace LedWallStudio
#endif //LEDWALLSTUDIO_MODE_H
