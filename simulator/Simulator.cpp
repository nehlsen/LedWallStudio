#include "Simulator.h"
#include "../src/BitmapEditor.h"
#include "support/FastLED.h"
#include "../../esp/LedWall/components/Mates-for-LEDs/LedMatrix/LedMatrix.h"
#include "../../esp/LedWall/main/LedMode/LedMode.h"

Simulator::Simulator(BitmapEditor *view, QObject *parent) :
    QObject(parent), m_view(view)
{
    const int width = m_view->getGridSize().width();
    const int height = m_view->getGridSize().height();

    m_controller = new CFastLED(m_view, width * height);
    m_matrix = new LedMatrix(*m_controller, width, height, MatrixOptions::MatrixStraight);

    m_tickTimer = new QTimer;
    m_tickTimer->setSingleShot(false);
    m_tickTimer->setInterval(40);
    connect(m_tickTimer, &QTimer::timeout, this, &Simulator::onTick);
}

LedMatrix *Simulator::getMatrix()
{
    return m_matrix;
}

void Simulator::setMode(LedWall::Mode::LedMode *modeToSimulate)
{
    bool restart = false;
    if (m_mode != nullptr) {
        restart = m_tickTimer->isActive();
        m_tickTimer->stop();
        delete m_mode;
    }

    m_mode = modeToSimulate;

    if (restart) {
        run();
    }
}

bool Simulator::isActive() const
{
    return m_tickTimer->isActive();
}

int Simulator::getFrameDelay() const
{
    return m_tickTimer->interval();
}

bool Simulator::isAutomaticFrameDelay() const
{
    return false;
}

void Simulator::run()
{
    if (m_mode == nullptr) {
        m_tickTimer->stop();
        return;
    }

    m_tickTimer->start();
}

void Simulator::start()
{
    run();
}

void Simulator::stop()
{
    m_tickTimer->stop();
}

void Simulator::setFrameDelay(int msec)
{
    m_tickTimer->setInterval(msec);
}

void Simulator::revertFrameDelay()
{
    if (m_mode == nullptr) {
        return;
    }

    m_tickTimer->setInterval(m_mode->frameDelay());
}

void Simulator::step()
{
    stop();
    onTick();
}

void Simulator::onTick()
{
    if (m_mode == nullptr) {
        m_tickTimer->stop();
        return;
    }

    m_mode->update();
    m_controller->show();
}
