#ifndef LEDWALLSTUDIO_CONFIG_H
#define LEDWALLSTUDIO_CONFIG_H

#include <QtCore/QString>
#include <QtCore/QJsonDocument>

namespace LedWall
{

class Config
{
public:
    static Config fromJson(const QJsonDocument &jsonDocument);
    QJsonDocument toJson() const;

    bool isValid() const;

    quint8 MatrixWidth = 0;
    quint8 MatrixHeight = 0;
    quint8 Brightness = 0;

    enum AutoPowerOn {
        ALWAYS_OFF = 0,
        ALWAYS_ON = 1,
        RECOVER_LAST = 2,
    };
    AutoPowerOn PowerOnResetMode = RECOVER_LAST;
    qint8 LedModeAutoRestore = 0;

    QString MqttBroker;
    QString MqttDeviceTopic;
    QString MqttGroupTopic;
};

} // namespace LedWall
#endif //LEDWALLSTUDIO_CONFIG_H
