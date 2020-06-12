#include "WallController.h"

WallController::WallController(QObject *parent) : QObject(parent)
{
}

bool WallController::isConnected() const
{
    return m_isConnected;
}

LedWallStudio::ModeList WallController::getModes() const
{
    return m_modes;
}

LedWallStudio::Mode WallController::getMode() const
{
    return m_mode;
}

void WallController::setIsConnected(bool isConnected)
{
    if (m_isConnected == isConnected) {
        return;
    }

    m_isConnected = isConnected;

    if (isConnected) emit connected();
    else emit disconnected();
    emit connectionStatusChanged(isConnected);
}

void WallController::updateModes(LedWallStudio::ModeList modes)
{
    m_modes = modes;
    emit modesChanged();
}

void WallController::updateMode(LedWallStudio::Mode mode)
{
    m_mode = mode;
    emit modeChanged();
}
