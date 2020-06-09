#ifndef LEDWALLSTUDIO_WAVEOPTIONSWIDGET_H
#define LEDWALLSTUDIO_WAVEOPTIONSWIDGET_H

#include "ModeOptionsWidget.h"

QT_BEGIN_NAMESPACE
class QComboBox;
class QSpinBox;
QT_END_NAMESPACE

class WaveOptionsWidget : public ModeOptionsWidget
{
Q_OBJECT

public:
    explicit WaveOptionsWidget(QWidget *parent = nullptr);

    void setOptions(const LedWallStudio::ModeOptions &options) override;
    LedWallStudio::ModeOptions getOptions() const override;

protected:
    void initUi();
    QComboBox *m_waveMode;
    QComboBox *m_waveDirection;
    QSpinBox *m_waveLength;
    QSpinBox *m_speed;

    QSpinBox *m_colorHueMin;
    QSpinBox *m_colorHueMax;

    QSpinBox *m_colorSaturationMin;
    QSpinBox *m_colorSaturationMax;

    QSpinBox *m_colorValueMin;
    QSpinBox *m_colorValueMax;
};

#endif //LEDWALLSTUDIO_WAVEOPTIONSWIDGET_H
