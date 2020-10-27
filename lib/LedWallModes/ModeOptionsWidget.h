#ifndef LEDWALLSTUDIO_MODEOPTIONSWIDGET_H
#define LEDWALLSTUDIO_MODEOPTIONSWIDGET_H

#include <QtWidgets/QWidget>
#include "../WallController/Mode.h"

class ModeOptionsWidget : public QWidget
{
Q_OBJECT

public:
    explicit ModeOptionsWidget(QWidget *parent = nullptr);
    virtual ~ModeOptionsWidget() = default;

    virtual void setOptions(const LedWallStudio::ModeOptions &options) = 0;
    virtual LedWallStudio::ModeOptions getOptions() const = 0;
};

#endif //LEDWALLSTUDIO_MODEOPTIONSWIDGET_H
