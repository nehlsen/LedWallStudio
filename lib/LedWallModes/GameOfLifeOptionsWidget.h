#ifndef LEDWALLSTUDIO_GAMEOFLIFEOPTIONSWIDGET_H
#define LEDWALLSTUDIO_GAMEOFLIFEOPTIONSWIDGET_H

#include "ModeOptionsWidget.h"

QT_BEGIN_NAMESPACE
class QSpinBox;
QT_END_NAMESPACE

class GameOfLifeOptionsWidget : public ModeOptionsWidget
{
Q_OBJECT

public:
    explicit GameOfLifeOptionsWidget(QWidget *parent = nullptr);

    void setOptions(const LedWallStudio::ModeOptions &options) override;
    LedWallStudio::ModeOptions getOptions() const override;

protected:
    void initUi();
    QSpinBox *m_generationDelay;
};

#endif //LEDWALLSTUDIO_GAMEOFLIFEOPTIONSWIDGET_H
