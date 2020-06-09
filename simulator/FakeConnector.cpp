#include "FakeConnector.h"
#include "Simulator.h"
#include "../../esp/LedWall/main/LedMode/LedModeStatus.h"
#include "../../esp/LedWall/main/LedMode/Bars.h"
#include "../../esp/LedWall/main/LedMode/MultiBars.h"
#include "../../esp/LedWall/main/LedMode/Breathe.h"
#include "../../esp/LedWall/main/LedMode/Fireworks.h"
#include "../../esp/LedWall/main/LedMode/Text.h"
#include "../../esp/LedWall/main/LedMode/MatesDemo.h"
#include "../../esp/LedWall/main/LedMode/Wave.h"
#include "ModeOptions.h"

FakeConnector::FakeConnector(Simulator *simulator, QObject *parent) :
    WallController(parent), m_simulator(simulator)
{
    init();
}

void FakeConnector::setModeByIndex(int modeIndex)
{
    LedWall::Mode::LedMode *newMode = nullptr;

    switch (modeIndex) {
        case 0:
            newMode = new LedWall::Mode::LedModeStatus(*m_simulator->getMatrix());
            break;

        case 1:
            newMode = new LedWall::Mode::Bars(*m_simulator->getMatrix());
            break;

        case 2:
            newMode = new LedWall::Mode::MultiBars(*m_simulator->getMatrix());
            break;

        case 3:
            newMode = new LedWall::Mode::MatesDemo(*m_simulator->getMatrix());
            break;

        case 4:
            newMode = new LedWall::Mode::Wave(*m_simulator->getMatrix());
            break;

        default:
            qWarning("FakeConnector::setModeByIndex - INVALID MODE INDEX");
            break;
    }

    m_simulator->setMode(newMode);
    for (auto& mode : m_modes) {
        if (mode.Index == modeIndex) {
            mode.Options = ModeOptions::readFromMode(newMode);
            updateMode(mode);
        }
    }
}

void FakeConnector::setModeByName(const QString &name)
{
    qWarning("FakeConnector::setModeByName - NOT IMPLEMENTED");
}

void FakeConnector::setModeOptions(const LedWallStudio::ModeOptions &options)
{
    ModeOptions::writeToMode(options, m_simulator->getMode());
}

void FakeConnector::init()
{
    LedWallStudio::Mode modeStatus;
    modeStatus.Index = 0;
    modeStatus.Name = "Status";

    LedWallStudio::Mode modeBars;
    modeBars.Index = 1;
    modeBars.Name = "Bars";

    LedWallStudio::Mode modeMultiBars;
    modeMultiBars.Index = 2;
    modeMultiBars.Name = "MultiBars";

    LedWallStudio::Mode modeMatesDemo;
    modeMatesDemo.Index = 3;
    modeMatesDemo.Name = "MatesDemo";

    LedWallStudio::Mode modeWave;
    modeWave.Index = 4;
    modeWave.Name = "Wave";

    // breath, fireworks, text

    LedWallStudio::ModeList modes;
    modes << modeStatus << modeBars << modeMultiBars << modeMatesDemo << modeWave;

    updateModes(modes);
//    updateMode(); // TODO
    setIsConnected(true);
}
