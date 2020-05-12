#ifndef LEDWALLSTUDIO_MODE_H
#define LEDWALLSTUDIO_MODE_H

#include <QtCore/QList>
#include <QtCore/QJsonDocument>

namespace LedWall
{

struct Mode
{
    quint8 Index;
    QString Name;
};

class ModeList : public QList<Mode>
{
public:
    static ModeList fromJson(const QJsonDocument &jsonDocument);
};

} // namespace LedWall
#endif //LEDWALLSTUDIO_MODE_H
