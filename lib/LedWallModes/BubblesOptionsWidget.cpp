#include "BubblesOptionsWidget.h"
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QFormLayout>

BubblesOptionsWidget::BubblesOptionsWidget(QWidget *parent) : ModeOptionsWidget(parent)
{
    initUi();
}

void BubblesOptionsWidget::setOptions(const LedWallStudio::ModeOptions &options)
{
    if (options.contains("numberOfBubbles")) {
        m_numberOfBubbles->setValue(options.value("numberOfBubbles").toInt());
    }
    if (options.contains("maximumBubbleSize")) {
        m_maximumBubbleSize->setValue(options.value("maximumBubbleSize").toInt());
    }
    if (options.contains("speed")) {
        m_speed->setValue(options.value("speed").toInt());
    }
    if (options.contains("maximumFrameDelay")) {
        m_maximumFrameDelay->setValue(options.value("maximumFrameDelay").toInt());
    }
}

LedWallStudio::ModeOptions BubblesOptionsWidget::getOptions() const
{
    LedWallStudio::ModeOptions options;

    options.insert("numberOfBubbles", m_numberOfBubbles->value());
    options.insert("maximumBubbleSize", m_maximumBubbleSize->value());
    options.insert("speed", m_speed->value());
    options.insert("maximumFrameDelay", m_maximumFrameDelay->value());

    return options;
}

void BubblesOptionsWidget::initUi()
{
    m_numberOfBubbles = new QSpinBox(this);
    m_numberOfBubbles->setRange(1, 10);

    m_maximumBubbleSize = new QSpinBox(this);
    m_maximumBubbleSize->setRange(1, 100);

    m_speed = new QSpinBox(this);
    m_speed->setRange(1, 255);

    m_maximumFrameDelay = new QSpinBox(this);
    m_maximumFrameDelay->setRange(1, 255);

    auto layout = new QFormLayout(this);
    layout->addRow(tr("Number of Bubbles"), m_numberOfBubbles);
    layout->addRow(tr("Maximum Bubble Size"), m_maximumBubbleSize);
    layout->addRow(tr("Speed"), m_speed);
    layout->addRow(tr("Maximum Frame Delay"), m_maximumFrameDelay);
    setLayout(layout);
}
