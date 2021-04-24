#include "MainWindow.h"
#include <BitmapEditor/BitmapEditor.h>
#include "UdpConnector.h"
#include "HttpConnector/HttpConnector.h"
#include "SettingsDialog.h"
#include "LedWallConfigWidget.h"
#include "LedWallModes/ModeConfigWidget.h"
#include "Animations/BitmapFramesWidget.h"
#include "Animations/FrameListWriter.h"
#include "Animations/FrameListReader.h"
#include <QtWidgets/QToolBar>
#include <QtWidgets/QColorDialog>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QDockWidget>
#include <QtCore/QCoreApplication>
#include <QtCore/QSettings>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>

namespace LedWall::Studio {

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("LedWall Studio");

    createBitmapEditor();

    m_udpConnector = new UdpConnector(this);
    m_httpConnector = new HttpConnector(this);
    connect(m_httpConnector, &HttpConnector::connectionStatusChanged, this, &MainWindow::onHttpConnectorConnectionChanged);
    connect(m_httpConnector, &HttpConnector::configChanged, this, &MainWindow::onHttpConnectorConfigChanged);

    createMenu();
    createToolbars();
    setCentralWidget(m_bitmapEditor);
    createDocks();

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
}

void MainWindow::onHttpConnectorConfigChanged()
{
    QSettings settings;
    if (settings.value("Settings/autodetect_size", false).toBool()) {
        m_bitmapEditor->setSize(m_httpConnector->getConfig().MatrixWidth, m_httpConnector->getConfig().MatrixHeight);
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
    QColor color = QColorDialog::getColor(m_bitmapEditor->getPrimaryColor(), this);
    if (color.isValid()) {
        m_bitmapEditor->setPrimaryColor(color);
    }
}

void MainWindow::onPickSecondaryColorTriggered()
{
    QColor color = QColorDialog::getColor(m_bitmapEditor->getSecondaryColor(), this);
    if (color.isValid()) {
        m_bitmapEditor->setSecondaryColor(color);
    }
}

void MainWindow::showSettings()
{
    auto *settingsDlg = new SettingsDialog(this);
    if (settingsDlg->exec() == QDialog::Accepted) {
        // TODO react to changed settings
    }
}

void MainWindow::loadFrames()
{
    if (QMessageBox::warning(
            this,
            tr("Discard Frames?"),
            tr("Opening a list of Frames will discard current Frames.\nDiscard Frames?"),
            QMessageBox::Ok | QMessageBox::Cancel,
            QMessageBox::Cancel) == QMessageBox::Cancel) {
        return;
    }

    QString loadFromName = QFileDialog::getOpenFileName(
            this,
            tr("Load Frames"),
            QSettings().value("Settings/bitmap_folder", QDir::homePath()).toString()
    );

    if (loadFromName.isEmpty()) {
        return;
    }

    QFile file(loadFromName);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    FrameList frames = FrameListReader::fromIoDevice(file);
    file.close();

    m_bitmapFramesWidget->setFrames(frames);
}

void MainWindow::saveFrames()
{
    QString saveToName = QFileDialog::getSaveFileName(
            this,
            tr("Save Frames"),
            QSettings().value("Settings/bitmap_folder", QDir::homePath()).toString()
    );

    if (saveToName.isEmpty()) {
        return;
    }

    QFile file(saveToName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return;
    }

    auto frames = m_bitmapFramesWidget->getFrames();
    if (frames.isEmpty()) {
        return;
    }

    QByteArray data = FrameListWriter::toByteArray(frames);
    file.write(data);
    file.close();
}

void MainWindow::sendBitmap() const
{
    m_udpConnector->sendBitmap(m_bitmapEditor->getBitmap());
}

void MainWindow::createBitmapEditor()
{
    m_bitmapEditor = new BitmapEditor(this);

    connect(m_bitmapEditor, SIGNAL(bitmapChanged()), this, SLOT(onBitmapChanged()));
}

void MainWindow::createMenu()
{
    auto *clearCanvasAction = new QAction(tr("Clear Canvas"), this);
    connect(clearCanvasAction, SIGNAL(triggered()), m_bitmapEditor, SLOT(clearCanvas()));

    auto *loadFramesAction = new QAction(tr("Load Frames"), this);
    connect(loadFramesAction, SIGNAL(triggered()), this, SLOT(loadFrames()));

    auto *saveFramesAction = new QAction(tr("Save Frames"), this);
    connect(saveFramesAction, SIGNAL(triggered()), this, SLOT(saveFrames()));

    auto *settingsAction = new QAction(tr("&Settings"), this);
    connect(settingsAction, SIGNAL(triggered()), this, SLOT(showSettings()));

    auto *exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    auto *fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(clearCanvasAction);
    fileMenu->addAction(loadFramesAction);
    fileMenu->addAction(saveFramesAction);
    fileMenu->addSeparator();
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

void MainWindow::createDocks()
{
    m_bitmapFramesWidget = new BitmapFramesWidget(m_bitmapEditor, this);
    auto *bitmapFramesDock = new QDockWidget(tr("Frames"), this);
    bitmapFramesDock->setObjectName("bitmapFramesDock");
    bitmapFramesDock->setWidget(m_bitmapFramesWidget);
    addDockWidget(Qt::LeftDockWidgetArea, bitmapFramesDock);

    m_modeWidget = new ModeConfigWidget(m_httpConnector, this);
    auto *modeDock = new QDockWidget(tr("Mode"), this);
    modeDock->setObjectName("modeDock");
    modeDock->setWidget(m_modeWidget);
    addDockWidget(Qt::RightDockWidgetArea, modeDock);

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

}
