#ifndef LEDWALLSTUDIO_PLAYBACKCONTROLWIDGET_H
#define LEDWALLSTUDIO_PLAYBACKCONTROLWIDGET_H

#include <QtWidgets/QWidget>

class Simulator;

class PlaybackControlWidget : public QWidget
{
Q_OBJECT

public:
    explicit PlaybackControlWidget(Simulator *simulator, QWidget *parent = nullptr);

protected slots:
    void onSpinFpsChanged(int fps);
    void onButtonStartStopToggled(bool checked);
    void onButtonStepClicked();

protected:
    Simulator *m_simulator;

    void createUi();
};

#endif //LEDWALLSTUDIO_PLAYBACKCONTROLWIDGET_H
