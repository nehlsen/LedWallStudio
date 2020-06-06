#ifndef LEDWALLSTUDIO_FAKECONNECTOR_H
#define LEDWALLSTUDIO_FAKECONNECTOR_H

#include "../src/WallController/WallController.h"

class Simulator;

class FakeConnector : public WallController
{
Q_OBJECT

public:
    explicit FakeConnector(Simulator *simulator, QObject *parent = nullptr);

    void setModeByIndex(int modeIndex) override;
    void setModeByName(const QString &name) override;

protected:
    Simulator *m_simulator;

    void init();
};

#endif //LEDWALLSTUDIO_FAKECONNECTOR_H
