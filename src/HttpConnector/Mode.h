#ifndef LEDWALLSTUDIO_MODE_H
#define LEDWALLSTUDIO_MODE_H

#include <QtCore/QList>
#include <QtCore/QJsonDocument>
#include <QtCore/QMap>

namespace LedWall
{

struct Mode
{
    static Mode fromJson(const QJsonObject &jsonObject);

    bool isValid() const;

    qint8 Index;
    QString Name;
    QMap<QString, QVariant> Options;
};

class ModeList : public QList<Mode>
{
public:
    static ModeList fromJson(const QJsonDocument &jsonDocument);
};

} // namespace LedWall
#endif //LEDWALLSTUDIO_MODE_H
