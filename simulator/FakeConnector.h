#ifndef LEDWALLSTUDIO_FAKECONNECTOR_H
#define LEDWALLSTUDIO_FAKECONNECTOR_H

#include <WallController/WallController.h>
#include <LedMode/LedModes.h>

typedef std::function<LedWall::Mode::LedMode *(LedMatrix &)> LambdaModeFactory_t;

class Simulator;

class FakeConnector : public WallController
{
Q_OBJECT

public:
    explicit FakeConnector(Simulator *simulator, QObject *parent = nullptr);

    void setModeByIndex(int modeIndex) override;
    void setModeByName(const QString &name) override;

    void setModeOptions(const LedWallStudio::ModeOptions &options) override;

protected:
    Simulator *m_simulator;

    void init();
    QList<LambdaModeFactory_t> m_modeFactories;
};

#endif //LEDWALLSTUDIO_FAKECONNECTOR_H
