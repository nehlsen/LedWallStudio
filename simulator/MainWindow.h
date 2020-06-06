#ifndef LEDWALLSTUDIO_MAINWINDOW_H
#define LEDWALLSTUDIO_MAINWINDOW_H

#include <QtWidgets/QMainWindow>

class Simulator;
class ModeConfigWidget;
class FakeConnector;
class BitmapEditor;

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

protected slots:

protected:
    void createSimulator();
    BitmapEditor *m_view;
    Simulator *m_simulator;

    void createFakeConnector();
    FakeConnector *m_fakeConnector;

    void creatDocks();
    ModeConfigWidget *m_modeWidget;
};

#endif //LEDWALLSTUDIO_MAINWINDOW_H
