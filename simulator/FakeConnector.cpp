#include "FakeConnector.h"
#include "Simulator.h"
#include "ModeOptions.h"
#include <LedMode/LedModeStatus.h>
#include <LedMode/Bars.h>
#include <LedMode/MultiBars.h>
#include <LedMode/Breathe.h>
#include <LedMode/Fireworks.h>
#include <LedMode/ModeText.h>
#include <LedMode/MatesDemo.h>
#include <LedMode/Wave.h>

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

        case 5:
            newMode = new LedWall::Mode::ModeText(*m_simulator->getMatrix());
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

    LedWallStudio::Mode modeText;
    modeText.Index = 5;
    modeText.Name = "Text";

    // breath, fireworks, text

    LedWallStudio::ModeList modes;
    modes << modeStatus << modeBars << modeMultiBars << modeMatesDemo << modeWave << modeText;

    updateModes(modes);
//    updateMode(); // TODO
    setIsConnected(true);
}
