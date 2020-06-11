#ifndef LEDWALLSTUDIO_TEXTOPTIONSWIDGET_H
#define LEDWALLSTUDIO_TEXTOPTIONSWIDGET_H

#include "ModeOptionsWidget.h"

QT_BEGIN_NAMESPACE
class QLineEdit;
class QSpinBox;
QT_END_NAMESPACE

class TextOptionsWidget : public ModeOptionsWidget
{
Q_OBJECT

public:
    explicit TextOptionsWidget(QWidget *parent = nullptr);

    void setOptions(const LedWallStudio::ModeOptions &options) override;
    LedWallStudio::ModeOptions getOptions() const override;

protected:
    void initUi();
    QLineEdit *m_text;
    QSpinBox *m_scrollSpeed;
};

#endif //LEDWALLSTUDIO_TEXTOPTIONSWIDGET_H
