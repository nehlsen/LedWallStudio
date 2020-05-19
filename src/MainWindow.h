#ifndef LEDWALLSTUDIO_MAINWINDOW_H
#define LEDWALLSTUDIO_MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QGraphicsView>

class BitmapEditor;
class UdpConnector;
class HttpConnector;
class LedWallConfigWidget;
class ModeConfigWidget;
class BitmapFramesWidget;

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

protected slots:
    void onHttpConnectorConnectionChanged(bool isConnected);
    void onHttpConnectorConfigChanged();

    void onBitmapChanged();
    void onPickPrimaryColorTriggered();
    void onPickSecondaryColorTriggered();
    void showSettings();
    void loadFrames() const;
    void saveFrames();
    void sendBitmap() const;

protected:
    void createBitmapEditor();
    BitmapEditor *m_bitmapEditor;

    UdpConnector *m_udpConnector;
    HttpConnector *m_httpConnector;

    void createMenu();
    void createToolbars();
    QAction *m_actionInstantUpdate;
    QAction *m_actionManualUpdate;

    void createDocks();
    BitmapFramesWidget *m_bitmapFramesWidget;
    ModeConfigWidget *m_modeWidget;
    LedWallConfigWidget *m_configWidget;

    void closeEvent(QCloseEvent *event) override;
};

#endif //LEDWALLSTUDIO_MAINWINDOW_H
