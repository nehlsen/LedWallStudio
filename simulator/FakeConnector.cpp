#include "FakeConnector.h"
#include "Simulator.h"
#include "ModeOptions.h"
#include "LedMode/FancyScript.h"
#include <QtCore/QDebug>
#include <LedMode/LedModeStatus.h>
#include <LedMode/Bars.h>
#include <LedMode/MultiBars.h>
#include <LedMode/ModeText.h>
#include <LedMode/ModeTime.h>
#include <LedMode/MatesDemo.h>
#include <LedMode/Wave.h>
#include <LedMode/FancyDemo.h>
#include <LedMode/NewYearsEve.h>
#include <LedMode/GameOfLife.h>
#include <LedMode/Hypocycloid.h>
#include <LedMode/Bubbles.h>

FakeConnector::FakeConnector(Simulator *simulator, QObject *parent) :
    WallController(parent), m_simulator(simulator)
{
    init();
}

void FakeConnector::setModeByIndex(int modeIndex)
{
    if (modeIndex >= m_modeFactories.size()) {
        qWarning("FakeConnector::setModeByIndex - INVALID MODE INDEX");
        return;
    }

    LedWallStudio::Mode studioMode = m_modes.at(modeIndex);
    LambdaModeFactory_t wallModeFactory = m_modeFactories.at(modeIndex);
    LedWall::Mode::LedMode *wallMode = wallModeFactory(*m_simulator->getMatrix());

    m_simulator->setMode(wallMode);
    studioMode.Options = ModeOptions::readFromMode(wallMode);
    updateMode(studioMode);
}

void FakeConnector::setModeByName(const QString &name)
{
    if (name.isEmpty()) {
        return;
    }

    const auto modeIt = std::find_if(m_modes.constBegin(), m_modes.constEnd(), [name](const LedWallStudio::Mode &mode) {
        return mode.Name == name;
    });
    if (modeIt != m_modes.constEnd()) {
        setModeByIndex(modeIt->Index);
        return;
    }

    qWarning() << QString("FakeConnector::setModeByName: FAILED! Mode '%1' not Found!").arg(name);
}

void FakeConnector::setModeOptions(const LedWallStudio::ModeOptions &options)
{
    ModeOptions::writeToMode(options, m_simulator->getMode());
}

void FakeConnector::init()
{
    LedWallStudio::ModeList modes;
    m_modeFactories.clear();
    
    auto addMode = [&modes, this](const QString &name, LambdaModeFactory_t factory) {
        qint8 nextIndex = modes.size();
        modes << LedWallStudio::Mode({nextIndex, name});
        m_modeFactories << factory;
    };
    
    addMode("Status", [this](LedMatrix &matrix) {
        return new LedWall::Mode::LedModeStatus(*m_simulator->getMatrix());
    });

    addMode("Bars", [this](LedMatrix &matrix) {
        return new LedWall::Mode::Bars(*m_simulator->getMatrix());
    });

    addMode("MultiBars", [this](LedMatrix &matrix) {
        return new LedWall::Mode::MultiBars(*m_simulator->getMatrix());
    });

    addMode("MatesDemo", [this](LedMatrix &matrix) {
        return new LedWall::Mode::MatesDemo(*m_simulator->getMatrix());
    });

    addMode("Wave", [this](LedMatrix &matrix) {
        return new LedWall::Mode::Wave(*m_simulator->getMatrix());
    });

    addMode("Text", [this](LedMatrix &matrix) {
        return new LedWall::Mode::ModeText(*m_simulator->getMatrix());
    });

    addMode("Time", [this](LedMatrix &matrix) {
        return new LedWall::Mode::ModeTime(*m_simulator->getMatrix());
    });

    addMode("FancyScript", [this](LedMatrix &matrix) {
        return new LedWall::Mode::FancyScript(*m_simulator->getMatrix());
    });

    addMode("FancyDemo", [this](LedMatrix &matrix) {
        return new LedWall::Mode::FancyDemo(*m_simulator->getMatrix());
    });

    addMode("NewYearsEve", [this](LedMatrix &matrix) {
        return new LedWall::Mode::NewYearsEve(*m_simulator->getMatrix());
    });

    addMode("GameOfLife", [this](LedMatrix &matrix) {
        return new LedWall::Mode::GameOfLife(*m_simulator->getMatrix());
    });

    addMode("Hypocycloid", [this](LedMatrix &matrix) {
        return new LedWall::Mode::Hypocycloid(*m_simulator->getMatrix());
    });

    addMode("Bubbles", [this](LedMatrix &matrix) {
        return new LedWall::Mode::Bubbles(*m_simulator->getMatrix());
    });

    // breath, fireworks

    updateModes(modes);
//    updateMode(); // TODO
    setIsConnected(true);
}
