#include "MainWindow.h"
#include "BitmapEditorCanvas.h"
#include "UdpConnector.h"
#include <QtWidgets/QToolBar>
#include <QtWidgets/QColorDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("LedWall Studio");

    m_view = new QGraphicsView(this);
    m_canvas = new BitmapEditorCanvas(this);
    m_view->setScene(m_canvas);
    connect(m_canvas, &BitmapEditorCanvas::bitmapChanged, this, &MainWindow::onBitmapChanged);

    m_connector = new UdpConnector(this);

    createToolbar();

    setCentralWidget(m_view);

    // TODO restoreState
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
