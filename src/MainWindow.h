#ifndef LEDWALLSTUDIO_MAINWINDOW_H
#define LEDWALLSTUDIO_MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QGraphicsView>

class BitmapEditorCanvas;
class UdpConnector;

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

protected slots:
    void onBitmapChanged();
    void onPickPrimaryColorTriggered();
    void onPickSecondaryColorTriggered();

protected:
    QGraphicsView *m_view;
    BitmapEditorCanvas *m_canvas;
    UdpConnector *m_connector;

    void createToolbar();
};

#endif //LEDWALLSTUDIO_MAINWINDOW_H
