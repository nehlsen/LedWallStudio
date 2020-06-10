#ifndef LEDWALLSTUDIO_MULTIBARSOPTIONSWIDGET_H
#define LEDWALLSTUDIO_MULTIBARSOPTIONSWIDGET_H

#include "ModeOptionsWidget.h"

class MultiBarsOptionsWidget : public ModeOptionsWidget
{
Q_OBJECT

public:
    explicit MultiBarsOptionsWidget(QWidget *parent = nullptr);

    void setOptions(const LedWallStudio::ModeOptions &options) override;
    LedWallStudio::ModeOptions getOptions() const override;
};

#endif //LEDWALLSTUDIO_MULTIBARSOPTIONSWIDGET_H
