#include "MainWindow.h"
#include "Simulator.h"
#include "FakeConnector.h"
#include "../src/LedWallModes/ModeConfigWidget.h"
#include <QtWidgets/QDockWidget>
#include "../src/BitmapEditor.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent)
{
    createSimulator();
    createFakeConnector();
    creatDocks();
}

void MainWindow::createSimulator()
{
    const int width = 10;
    const int height = 1;

    m_view = new BitmapEditor(this);
    m_view->setGridSize({width, height});
    m_view->show();
    m_simulator = new Simulator(m_view, this);
    setCentralWidget(m_view);

    m_simulator->run(); // FIXME replace with play/pause button
}

void MainWindow::createFakeConnector()
{
    m_fakeConnector = new FakeConnector(m_simulator, this);
}

void MainWindow::creatDocks()
{
    m_modeWidget = new ModeConfigWidget(m_fakeConnector, this);
    auto *modeDock = new QDockWidget(tr("Mode"), this);
    modeDock->setObjectName("modeDock");
    modeDock->setWidget(m_modeWidget);
    addDockWidget(Qt::RightDockWidgetArea, modeDock);

    // combo mode
    // frame rate 1/s 40/s pause step
    // mode options?
}
