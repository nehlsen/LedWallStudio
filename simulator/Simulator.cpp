#include "Simulator.h"
#include "../src/BitmapEditor.h"
#include "support/FastLED.h"
#include "../../esp/LedWall/components/Mates-for-LEDs/LedMatrix/LedMatrix.h"
#include "../../esp/LedWall/main/LedMode/LedMode.h"

Simulator::Simulator()
{
    const int width = 25;
    const int height = 16;

    m_view = new BitmapEditor;
    m_view->setSize({width, height});
    m_controller = new CLEDController(m_view, width * height);
    m_matrix = new LedMatrix(*m_controller, width, height, MatrixOptions::MatrixStraight);

    m_tickTimer = new QTimer;
    m_tickTimer->setSingleShot(false);
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
        m_tickTimer->stop();
        delete m_mode;
        restart = true;
    }

    m_mode = modeToSimulate;

    if (restart) {
        run();
    }
}

void Simulator::run()
{
    if (m_mode == nullptr) {
        m_tickTimer->stop();
        return;
    }

    m_tickTimer->setInterval(m_mode->frameDelay());
//    m_tickTimer->setInterval(1000);
    m_tickTimer->start();

    m_view->show();
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
