#ifndef LEDWALLSTUDIO_FANCYSCRIPTOPTIONSWIDGET_H
#define LEDWALLSTUDIO_FANCYSCRIPTOPTIONSWIDGET_H

#include "ModeOptionsWidget.h"

QT_BEGIN_NAMESPACE
class QPlainTextEdit;
QT_END_NAMESPACE

class FancyScriptOptionsWidget : public ModeOptionsWidget
{
Q_OBJECT

public:
    explicit FancyScriptOptionsWidget(QWidget *parent = nullptr);

    void setOptions(const LedWallStudio::ModeOptions &options) override;
    LedWallStudio::ModeOptions getOptions() const override;

protected:
    void initUi();
    QPlainTextEdit *m_script;
};

#endif //LEDWALLSTUDIO_FANCYSCRIPTOPTIONSWIDGET_H
