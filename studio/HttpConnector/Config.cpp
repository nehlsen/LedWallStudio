#include "Config.h"
#include <QtCore/QJsonObject>

bool LedWall::Config::operator==(const LedWall::Config &other) const
{
    return
        MatrixWidth == other.MatrixWidth &&
        MatrixHeight == other.MatrixHeight &&
        Brightness == other.Brightness &&
        PowerOnResetMode == other.PowerOnResetMode &&
        LedModeAutoRestore == other.LedModeAutoRestore &&
        MqttBroker == other.MqttBroker &&
        MqttDeviceTopic == other.MqttDeviceTopic &&
        MqttGroupTopic == other.MqttGroupTopic;
}

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

    config.PowerOnResetMode = (AutoPowerOn)jsonConfig.value("PowerOnResetMode").toInt();
    config.LedModeAutoRestore = jsonConfig.value("LedModeAutoRestore").toInt();

    config.MqttBroker = jsonConfig.value("MqttBroker").toString();
    config.MqttDeviceTopic = jsonConfig.value("MqttDeviceTopic").toString();
    config.MqttGroupTopic = jsonConfig.value("MqttGroupTopic").toString();

    return config;
}

QJsonDocument LedWall::Config::toJson() const
{
    QJsonObject config;
    config.insert("MatrixWidth", MatrixWidth);
    config.insert("MatrixHeight", MatrixHeight);
    config.insert("Brightness", Brightness);
    config.insert("PowerOnResetMode", PowerOnResetMode);
    config.insert("LedModeAutoRestore", LedModeAutoRestore);
    config.insert("MqttBroker", MqttBroker);
    config.insert("MqttDeviceTopic", MqttDeviceTopic);
    config.insert("MqttGroupTopic", MqttGroupTopic);

    return QJsonDocument(config);
}

bool LedWall::Config::isValid() const
{
    return MatrixWidth != 0 && MatrixHeight != 0;
}

QJsonDocument LedWall::Config::deltaAsJson(const LedWall::Config &updatedConfig) const
{
    QJsonObject config;
    if (MatrixWidth != updatedConfig.MatrixWidth) config.insert("MatrixWidth", updatedConfig.MatrixWidth);
    if (MatrixHeight != updatedConfig.MatrixHeight) config.insert("MatrixHeight", updatedConfig.MatrixHeight);
    if (Brightness != updatedConfig.Brightness) config.insert("Brightness", updatedConfig.Brightness);
    if (PowerOnResetMode != updatedConfig.PowerOnResetMode) config.insert("PowerOnResetMode", updatedConfig.PowerOnResetMode);
    if (LedModeAutoRestore != updatedConfig.LedModeAutoRestore) config.insert("LedModeAutoRestore", updatedConfig.LedModeAutoRestore);
    if (MqttBroker != updatedConfig.MqttBroker) config.insert("MqttBroker", updatedConfig.MqttBroker);
    if (MqttDeviceTopic != updatedConfig.MqttDeviceTopic) config.insert("MqttDeviceTopic", updatedConfig.MqttDeviceTopic);
    if (MqttGroupTopic != updatedConfig.MqttGroupTopic) config.insert("MqttGroupTopic", updatedConfig.MqttGroupTopic);

    return QJsonDocument(config);
}
