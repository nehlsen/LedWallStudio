#ifndef LEDWALLSTUDIO_TIMEOPTIONSWIDGET_H
#define LEDWALLSTUDIO_TIMEOPTIONSWIDGET_H

#include "TextOptionsWidget.h"

QT_BEGIN_NAMESPACE
class QLineEdit;
class QSpinBox;
class QComboBox;
QT_END_NAMESPACE

class TimeOptionsWidget : public TextOptionsWidget
{
Q_OBJECT

public:
    explicit TimeOptionsWidget(QWidget *parent = nullptr);

    void setOptions(const LedWallStudio::ModeOptions &options) override;
    LedWallStudio::ModeOptions getOptions() const override;

protected:
    void initUi();
    QComboBox *m_variant;
    QSpinBox *m_variantParameter;
};

#endif //LEDWALLSTUDIO_TIMEOPTIONSWIDGET_H
