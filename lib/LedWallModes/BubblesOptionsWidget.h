#ifndef LEDWALLSTUDIO_BUBBLESOPTIONSWIDGET_H
#define LEDWALLSTUDIO_BUBBLESOPTIONSWIDGET_H

#include "ModeOptionsWidget.h"

QT_BEGIN_NAMESPACE
class QSpinBox;
QT_END_NAMESPACE

class BubblesOptionsWidget : public ModeOptionsWidget
{
Q_OBJECT

public:
    explicit BubblesOptionsWidget(QWidget *parent = nullptr);

    void setOptions(const LedWallStudio::ModeOptions &options) override;
    LedWallStudio::ModeOptions getOptions() const override;

protected:
    void initUi();
    QSpinBox *m_numberOfBubbles;
    QSpinBox *m_maximumBubbleSize;
    QSpinBox *m_speed;
    QSpinBox *m_maximumFrameDelay;
};

#endif //LEDWALLSTUDIO_BUBBLESOPTIONSWIDGET_H
