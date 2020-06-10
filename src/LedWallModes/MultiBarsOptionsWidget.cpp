#include "MultiBarsOptionsWidget.h"

MultiBarsOptionsWidget::MultiBarsOptionsWidget(QWidget *parent) : ModeOptionsWidget(parent)
{
}

void MultiBarsOptionsWidget::setOptions(const LedWallStudio::ModeOptions &options)
{
}

LedWallStudio::ModeOptions MultiBarsOptionsWidget::getOptions() const
{
    return LedWallStudio::ModeOptions();
}
