#include <QtWidgets/QApplication>
#include "../src/BitmapEditor.h"
#include "../../esp/LedWall/components/Mates-for-LEDs/LedMatrix/LedMatrix.h"
#include "../../esp/LedWall/main/LedMode/LedModeStatus.h"
#include "../../esp/LedWall/main/LedMode/Bars.h"
#include "../../esp/LedWall/main/LedMode/MultiBars.h"
//#include "../../esp/LedWall/main/LedMode/Breathe.h"
//#include "../../esp/LedWall/main/LedMode/Fire.h"
#include "../../esp/LedWall/main/LedMode/Fireworks.h"
#include "../../esp/LedWall/main/LedMode/Text.h"
#include "Simulator.h"

int main(int argc, char* argv[])
{
    QApplication::setOrganizationName("nehlsen");
    QApplication::setApplicationName("ledwall-studio-simulator");
    QApplication app(argc, argv);

    auto *simulator = new Simulator();
//    auto *modeToSimulate = new LedWall::Mode::LedModeStatus(*simulator->getMatrix());
//    auto *modeToSimulate = new LedWall::Mode::Bars(*simulator->getMatrix());
    auto *modeToSimulate = new LedWall::Mode::MultiBars(*simulator->getMatrix());
//    auto *modeToSimulate = new LedWall::Mode::Breathe(*simulator->getMatrix());
//    auto *modeToSimulate = new LedWall::Mode::Fire(*simulator->getMatrix());
//    auto *modeToSimulate = new LedWall::Mode::Fireworks(*simulator->getMatrix());
//    auto *modeToSimulate = new LedWall::Mode::Text(*simulator->getMatrix());
    simulator->setMode(modeToSimulate);
    simulator->run();

    return app.exec();
}
