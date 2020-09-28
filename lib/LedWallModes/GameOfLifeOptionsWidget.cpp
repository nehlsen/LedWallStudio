#include "GameOfLifeOptionsWidget.h"
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QSpinBox>

GameOfLifeOptionsWidget::GameOfLifeOptionsWidget(QWidget *parent) : ModeOptionsWidget(parent)
{
    initUi();
}

void GameOfLifeOptionsWidget::setOptions(const LedWallStudio::ModeOptions &options)
{
    if (options.contains("generationDelay")) {
        m_generationDelay->setValue(options.value("generationDelay").toInt());
    }
}

LedWallStudio::ModeOptions GameOfLifeOptionsWidget::getOptions() const
{
    LedWallStudio::ModeOptions options;

    options.insert("generationDelay", m_generationDelay->value());

    return options;
}

void GameOfLifeOptionsWidget::initUi()
{
    m_generationDelay = new QSpinBox(this);
    m_generationDelay->setRange(25, 5000);

    auto layout = new QFormLayout(this);
    layout->addRow(tr("Generation Delay"), m_generationDelay);
    setLayout(layout);
}
