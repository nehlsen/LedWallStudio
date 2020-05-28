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
class CLEDController;
class LedMatrix;

class Simulator : public QObject
{
Q_OBJECT

public:
    Simulator();

    LedMatrix *getMatrix();
    void setMode(LedWall::Mode::LedMode *modeToSimulate);

public slots:
    void run();

protected slots:
    void onTick();

protected:
    BitmapEditor *m_view;
    CLEDController *m_controller;
    LedMatrix *m_matrix;

    LedWall::Mode::LedMode *m_mode = nullptr;
    QTimer *m_tickTimer;
};

#endif //LEDWALLSTUDIO_SIMULATOR_H
