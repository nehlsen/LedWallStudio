#include "MainWindow.h"
#include "BitmapEditorCanvas.h"
#include "UdpConnector.h"
#include "HttpConnector/HttpConnector.h"
#include "SettingsDialog.h"
#include "LedWallConfigWidget.h"
#include <QtWidgets/QToolBar>
#include <QtWidgets/QColorDialog>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QDockWidget>
#include <QtCore/QCoreApplication>
#include <QtCore/QSettings>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("LedWall Studio");

    createCanvas();

    m_udpConnector = new UdpConnector(this);
    m_httpConnector = new HttpConnector(this);
    connect(m_httpConnector, &HttpConnector::connectionStatusChanged, this, &MainWindow::onHttpConnectorConnectionChanged);

    createMenu();
    createToolbars();
    setCentralWidget(m_view);
    createConfigDock();

    QSettings settings;
    settings.beginGroup("MainWindow");
    restoreState(settings.value("State").toByteArray());
    restoreGeometry(settings.value("Geometry").toByteArray());
    m_actionInstantUpdate->setChecked(settings.value("InstantUpdateChecked").toBool());
}

void MainWindow::onHttpConnectorConnectionChanged(bool isConnected)
{
    m_actionInstantUpdate->setEnabled(isConnected);
    m_actionManualUpdate->setEnabled(isConnected);

    QSettings settings;
    if (isConnected && settings.value("Settings/autodetect_size", false).toBool()) {
        m_canvas->setSize(m_httpConnector->getConfig().MatrixWidth, m_httpConnector->getConfig().MatrixHeight);
        settings.setValue("Settings/width", m_httpConnector->getConfig().MatrixWidth);
        settings.setValue("Settings/height", m_httpConnector->getConfig().MatrixHeight);
    }
}

void MainWindow::onBitmapChanged()
{
    if (!m_actionInstantUpdate->isChecked()) {
        return;
    }

    sendBitmap();
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

void MainWindow::sendBitmap() const
{
    m_udpConnector->sendBitmap(m_canvas->getBitmap());
}

void MainWindow::createCanvas()
{
    m_view = new QGraphicsView(this);
    m_canvas = new BitmapEditorCanvas(this);
    m_view->setScene(m_canvas);
    connect(m_canvas, &BitmapEditorCanvas::bitmapChanged, this, &MainWindow::onBitmapChanged);
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

void MainWindow::createToolbars()
{
    auto *colorsToolbar = new QToolBar(this);
    colorsToolbar->setObjectName("colors-toolbar");

    auto *pickPrimaryColorAction = colorsToolbar->addAction(tr("Pick primary color"));
    connect(pickPrimaryColorAction, &QAction::triggered, this, &MainWindow::onPickPrimaryColorTriggered);

    auto *pickSecondaryColorAction = colorsToolbar->addAction(tr("Pick secondary color"));
    connect(pickSecondaryColorAction, &QAction::triggered, this, &MainWindow::onPickSecondaryColorTriggered);

    auto *connectionToolbar = new QToolBar(this);
    connectionToolbar->setObjectName("connection-toolbar");

    m_actionInstantUpdate = connectionToolbar->addAction(tr("Instant Update"));
    m_actionInstantUpdate->setCheckable(true);

    m_actionManualUpdate = connectionToolbar->addAction(tr("Update"));
    connect(m_actionManualUpdate, &QAction::triggered, this, &MainWindow::sendBitmap);

    auto *actionConnect = connectionToolbar->addAction(tr("Re/Connect"));
    connect(actionConnect, &QAction::triggered, m_httpConnector, &HttpConnector::connectToWall);

    addToolBar(colorsToolbar);
    addToolBar(connectionToolbar);
}

void MainWindow::createConfigDock()
{
    m_configWidget = new LedWallConfigWidget(m_httpConnector, this);

    auto *configDock = new QDockWidget(tr("Config"), this);
    configDock->setObjectName("configDock");
    configDock->setWidget(m_configWidget);
    addDockWidget(Qt::RightDockWidgetArea, configDock);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings;
    settings.beginGroup("MainWindow");
    settings.setValue("State", saveState());
    settings.setValue("Geometry", saveGeometry());
    settings.setValue("InstantUpdateChecked", m_actionInstantUpdate->isChecked());

    QWidget::closeEvent(event);
}
