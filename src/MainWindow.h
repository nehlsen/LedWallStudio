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
    void showSettings();

protected:
    QGraphicsView *m_view;
    BitmapEditorCanvas *m_canvas;
    UdpConnector *m_connector;

    void createMenu();
    void createToolbar();

    void closeEvent(QCloseEvent *event) override;
};

#endif //LEDWALLSTUDIO_MAINWINDOW_H
