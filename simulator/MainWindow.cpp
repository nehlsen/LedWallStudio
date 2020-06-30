#include "MainWindow.h"
#include "Simulator.h"
#include "FakeConnector.h"
#include "PlaybackControlWidget.h"
#include <LedWallModes/ModeConfigWidget.h>
#include <QtWidgets/QDockWidget>
#include <QtCore/QSettings>
#include <BitmapEditor/BitmapEditor.h>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent)
{
    createSimulator();
    createFakeConnector();
    creatDocks();
    loadWindowSettings();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveWindowSettings();
    QWidget::closeEvent(event);
}

void MainWindow::loadWindowSettings()
{
    QSettings settings;
    settings.beginGroup("Window");
    restoreState(settings.value("State").toByteArray());
    restoreGeometry(settings.value("Geometry").toByteArray());
}

void MainWindow::saveWindowSettings()
{
    QSettings settings;
    settings.beginGroup("Window");
    settings.setValue("State", saveState());
    settings.setValue("Geometry", saveGeometry());
}

void MainWindow::createSimulator()
{
    QSettings settings;
    if (!settings.contains("Grid/Size")) {
        settings.setValue("Grid/Size", QSize(5, 5));
    }
    if (!settings.contains("Grid/Mode")) {
        settings.setValue("Grid/Mode", BitmapEditor::GridModeRect);
    }
    QSize gridSize = settings.value("Grid/Size", QSize(5, 5)).toSize();
    BitmapEditor::GridMode gridMode = static_cast<BitmapEditor::GridMode>(settings.value("Grid/Mode", BitmapEditor::GridModeRect).toInt());

    m_view = new BitmapEditor(gridMode, this);
    m_view->setGridSize(gridSize);
    m_view->show();
    m_simulator = new Simulator(m_view, this);
    setCentralWidget(m_view);
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

    m_playbackControlWidget = new PlaybackControlWidget(m_simulator, this);
    auto *playbackControlDock = new QDockWidget(tr("Playback Control"), this);
    playbackControlDock->setObjectName("playbackControlDock");
    playbackControlDock->setWidget(m_playbackControlWidget);
    addDockWidget(Qt::RightDockWidgetArea, playbackControlDock);

    // combo mode
    // frame rate 1/s 40/s pause step
    // mode options?
}
