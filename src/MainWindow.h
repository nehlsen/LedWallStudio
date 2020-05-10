#ifndef LEDWALLSTUDIO_MAINWINDOW_H
#define LEDWALLSTUDIO_MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QGraphicsView>

class BitmapEditorCanvas;
class UdpConnector;
class HttpConnector;

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

protected slots:
    void onHttpConnectorConnectionChanged(bool isConnected);

    void onBitmapChanged();
    void onPickPrimaryColorTriggered();
    void onPickSecondaryColorTriggered();
    void showSettings();
    void sendBitmap() const;

protected:
    void createCanvas();
    QGraphicsView *m_view;
    BitmapEditorCanvas *m_canvas;

    UdpConnector *m_udpConnector;
    HttpConnector *m_httpConnector;

    void createMenu();
    void createToolbars();
    QAction *m_actionInstantUpdate;
    QAction *m_actionManualUpdate;

    void closeEvent(QCloseEvent *event) override;
};

#endif //LEDWALLSTUDIO_MAINWINDOW_H
