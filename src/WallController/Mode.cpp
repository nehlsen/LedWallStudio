#include "Mode.h"
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>

LedWallStudio::Mode LedWallStudio::Mode::fromJson(const QJsonObject &jsonObject)
{
    LedWallStudio::Mode mode = {-1, ""};

    if (jsonObject.contains("index")) {
        mode.Index = (qint8)jsonObject.value("index").toInt();
    }
    if (jsonObject.contains("name")) {
        mode.Name = jsonObject.value("name").toString();
    }
    if (jsonObject.contains("options")) {
        auto optionsObject = jsonObject.value("options").toObject();
        for (auto it = optionsObject.constBegin(); it != optionsObject.constEnd(); ++it) {
            mode.Options[it.key()] = it.value().toVariant();
        }
    }

    return mode;
}

bool LedWallStudio::Mode::isValid() const
{
    return Index != -1;
}

LedWallStudio::ModeList LedWallStudio::ModeList::fromJson(const QJsonDocument &jsonDocument)
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
