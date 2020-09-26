#ifndef LEDWALLSTUDIO_MULTIBARSOPTIONSWIDGET_H
#define LEDWALLSTUDIO_MULTIBARSOPTIONSWIDGET_H

#include "ModeOptionsWidget.h"

QT_BEGIN_NAMESPACE
class QSpinBox;
QT_END_NAMESPACE

class MultiBarsOptionsWidget : public ModeOptionsWidget
{
Q_OBJECT

public:
    explicit MultiBarsOptionsWidget(QWidget *parent = nullptr);

    void setOptions(const LedWallStudio::ModeOptions &options) override;
    LedWallStudio::ModeOptions getOptions() const override;

protected:
    void initUi();
    QSpinBox *m_fadeRate;
    QSpinBox *m_barTravelSpeed;
    QSpinBox *m_numberOfBars;
    QSpinBox *m_maximumFrameDelay;
};

#endif //LEDWALLSTUDIO_MULTIBARSOPTIONSWIDGET_H
