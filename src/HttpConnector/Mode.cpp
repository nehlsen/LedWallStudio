#include "Mode.h"
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>

LedWall::ModeList LedWall::ModeList::fromJson(const QJsonDocument &jsonDocument)
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
        const QJsonObject &jsonMode = it->toObject();
        if (!jsonMode.contains("index") || !jsonMode.contains("name")) {
            continue;
        }

        modes.append({
            (quint8) jsonMode.value("index").toInt(),
            jsonMode.value("name").toString()
        });
    }

    return modes;
}
