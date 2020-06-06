#ifndef LEDWALLSTUDIO_SIMULATOR_H
#define LEDWALLSTUDIO_SIMULATOR_H

#include <QtCore/QObject>
#include <QtCore/QTimer>

namespace LedWall {
namespace Mode {
class LedMode;
}
}
class BitmapEditor;
class CFastLED;
class LedMatrix;

class Simulator : public QObject
{
Q_OBJECT

public:
    explicit Simulator(BitmapEditor *view, QObject *parent = nullptr);

    LedMatrix *getMatrix();
    void setMode(LedWall::Mode::LedMode *modeToSimulate);

    bool isActive() const;
    int getFrameDelay() const;
    bool isAutomaticFrameDelay() const;

public slots:
    void run();

    void start();
    void stop();
    void setFrameDelay(int msec);
    void revertFrameDelay();

    // if isActive toggles pause
    void step();

protected slots:
    void onTick();

protected:
    BitmapEditor *m_view;
    CFastLED *m_controller;
    LedMatrix *m_matrix;

    LedWall::Mode::LedMode *m_mode = nullptr;
    QTimer *m_tickTimer;
};

#endif //LEDWALLSTUDIO_SIMULATOR_H
