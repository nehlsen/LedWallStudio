#include "Mode.h"
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>

namespace LedWallStudio
{

ModeOptions ModeOptions::fromJson(const QJsonObject &optionsObject)
{
    ModeOptions that;
    that.readJson(optionsObject);
    return that;
}

void ModeOptions::readJson(const QJsonObject &optionsObject)
{
    for (auto it = optionsObject.constBegin(); it != optionsObject.constEnd(); ++it) {
        (*this)[it.key()] = it.value().toVariant();
    }
}

QJsonObject ModeOptions::toJson() const
{
    QJsonObject jsonObject;
    for (auto it = constBegin(); it != constEnd(); ++it) {
        jsonObject.insert(it.key(), QJsonValue::fromVariant(it.value()));
    }

    return jsonObject;
}

Mode Mode::fromJson(const QJsonObject &jsonObject)
{
    Mode mode = {-1, ""};

    if (jsonObject.contains("index")) {
        mode.Index = (qint8)jsonObject.value("index").toInt();
    }
    if (jsonObject.contains("name")) {
        mode.Name = jsonObject.value("name").toString();
    }
    if (jsonObject.contains("options")) {
        mode.Options.readJson(jsonObject.value("options").toObject());
    }

    return mode;
}

bool Mode::isValid() const
{
    return Index != -1;
}

ModeList ModeList::fromJson(const QJsonDocument &jsonDocument)
{
    ModeList modes;

    if (!jsonDocument.isObject()) {
        return modes;
    }
    if (!jsonDocument.object().contains("modes") || !jsonDocument.object().value("modes").isArray()) {
        return modes;
    }

    QJsonArray jsonModes = jsonDocument.object().value("modes").toArray();
    for (QJsonArray::const_iterator it = jsonModes.constBegin(); it != jsonModes.constEnd(); ++it) {
        if (!it->isObject()) {
            continue;
        }
        Mode mode = Mode::fromJson(it->toObject());
        if (!mode.isValid()) {
            continue;
        }

        modes.append(mode);
    }

    return modes;
}

} // namespace LedWallStudio
