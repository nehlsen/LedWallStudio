#include "MainWindow.h"
#include "BitmapEditorCanvas.h"
#include "UdpConnector.h"
#include "SettingsDialog.h"
#include <QtWidgets/QToolBar>
#include <QtWidgets/QColorDialog>
#include <QtWidgets/QMenuBar>
#include <QtCore/QCoreApplication>
#include <QtCore/QSettings>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("LedWall Studio");

    m_view = new QGraphicsView(this);
    m_canvas = new BitmapEditorCanvas(this);
    m_view->setScene(m_canvas);
    connect(m_canvas, &BitmapEditorCanvas::bitmapChanged, this, &MainWindow::onBitmapChanged);

    m_connector = new UdpConnector(this);

    createMenu();
    createToolbar();
    setCentralWidget(m_view);

    QSettings settings;
    settings.beginGroup("MainWindow");
    restoreState(settings.value("State").toByteArray());
    restoreGeometry(settings.value("Geometry").toByteArray());
}

void MainWindow::createMenu()
{
    auto *clearCanvasAction = new QAction(tr("Clear Canvas"), this);
    connect(clearCanvasAction, SIGNAL(triggered()), m_canvas, SLOT(clearCanvas()));

    auto *settingsAction = new QAction(tr("&Settings"), this);
    connect(settingsAction, SIGNAL(triggered()), this, SLOT(showSettings()));

    auto *exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    auto *fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(clearCanvasAction);
    fileMenu->addAction(settingsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
    menuBar()->addMenu(fileMenu);

    auto *aboutQtAction = new QAction(tr("About &Qt"), this);
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    auto *helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutQtAction);
    menuBar()->addMenu(helpMenu);
}

void MainWindow::createToolbar()
{
    auto *toolbar = new QToolBar(this);

    auto *pickPrimaryColorAction = toolbar->addAction(tr("Pick primary color"));
    connect(pickPrimaryColorAction, &QAction::triggered, this, &MainWindow::onPickPrimaryColorTriggered);

    auto *pickSecondaryColorAction = toolbar->addAction(tr("Pick secondary color"));
    connect(pickSecondaryColorAction, &QAction::triggered, this, &MainWindow::onPickSecondaryColorTriggered);

    addToolBar(toolbar);
}

void MainWindow::onBitmapChanged()
{
    m_connector->sendBitmap(m_canvas->getBitmap());
}

void MainWindow::onPickPrimaryColorTriggered()
{
    QColor color = QColorDialog::getColor(m_canvas->getPrimaryColor(), this);
    if (color.isValid()) {
        m_canvas->setPrimaryColor(color);
    }
}

void MainWindow::onPickSecondaryColorTriggered()
{
    QColor color = QColorDialog::getColor(m_canvas->getSecondaryColor(), this);
    if (color.isValid()) {
        m_canvas->setSecondaryColor(color);
    }
}

void MainWindow::showSettings()
{
    auto *settingsDlg = new SettingsDialog(this);
    if (settingsDlg->exec() == QDialog::Accepted) {
        // TODO react to changed settings
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings;
    settings.beginGroup("MainWindow");
    settings.setValue("State", saveState());
    settings.setValue("Geometry", saveGeometry());

    QWidget::closeEvent(event);
}
