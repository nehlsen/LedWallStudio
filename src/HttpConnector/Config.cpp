#include "Config.h"
#include <QtCore/QJsonObject>

LedWall::Config LedWall::Config::fromJson(const QJsonDocument &jsonDocument)
{
    auto config = LedWall::Config();

    if (!jsonDocument.isObject()) {
        return config;
    }

    auto jsonConfig = jsonDocument.object();
    config.MatrixWidth = jsonConfig.value("MatrixWidth").toInt();
    config.MatrixHeight = jsonConfig.value("MatrixHeight").toInt();
    config.Brightness = jsonConfig.value("Brightness").toInt();

    config.PowerOnResetMode = jsonConfig.value("PowerOnResetMode").toInt();
    config.LedModeAutoRestore = jsonConfig.value("LedModeAutoRestore").toInt();

    config.MqttBroker = jsonConfig.value("MqttBroker").toString();
    config.MqttDeviceTopic = jsonConfig.value("MqttDeviceTopic").toString();
    config.MqttGroupTopic = jsonConfig.value("MqttGroupTopic").toString();

    return config;
}

QJsonDocument LedWall::Config::toJson() const
{
    qDebug("TODO LedWall::Config::toJson");
    // TODO
    return QJsonDocument();
}

bool LedWall::Config::isValid() const
{
    return MatrixWidth != 0 && MatrixHeight != 0;
}
