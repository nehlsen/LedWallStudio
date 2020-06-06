#ifndef LEDWALLSTUDIO_WALLCONTROLLER_H
#define LEDWALLSTUDIO_WALLCONTROLLER_H

#include <QtCore/QObject>
#include "Mode.h"

class WallController : public QObject
{
Q_OBJECT

public:
    explicit WallController(QObject *parent = nullptr);

    bool isConnected() const;

    LedWallStudio::ModeList getModes() const;
    LedWallStudio::Mode getMode() const;

    virtual void setModeByIndex(int modeIndex) = 0;
    virtual void setModeByName(const QString &name) = 0;

signals:
    void connected();
    void disconnected();
    void connectionStatusChanged(bool isConnected);

    void modesChanged();
    void modeChanged();

protected:
    bool m_isConnected = false;
    void setIsConnected(bool isConnected);

    LedWallStudio::ModeList m_modes;
    void updateModes(LedWallStudio::ModeList modes);
    LedWallStudio::Mode m_mode;
    void updateMode(LedWallStudio::Mode mode);
};

#endif //LEDWALLSTUDIO_WALLCONTROLLER_H
