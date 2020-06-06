#ifndef LEDWALLSTUDIO_MAINWINDOW_H
#define LEDWALLSTUDIO_MAINWINDOW_H

#include <QtWidgets/QMainWindow>

class Simulator;
class ModeConfigWidget;
class FakeConnector;
class BitmapEditor;
class PlaybackControlWidget;

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
    PlaybackControlWidget *m_playbackControlWidget;
};

#endif //LEDWALLSTUDIO_MAINWINDOW_H
