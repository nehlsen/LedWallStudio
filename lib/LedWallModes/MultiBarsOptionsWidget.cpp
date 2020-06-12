#include "MultiBarsOptionsWidget.h"
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>

MultiBarsOptionsWidget::MultiBarsOptionsWidget(QWidget *parent) : ModeOptionsWidget(parent)
{
    initUi();
}

void MultiBarsOptionsWidget::setOptions(const LedWallStudio::ModeOptions &options)
{
    if (options.contains("fadeRate")) {
        m_fadeRate->setValue(options.value("fadeRate").toInt());
    }
    if (options.contains("barTravelSpeed")) {
        m_barTravelSpeed->setValue(options.value("barTravelSpeed").toInt());
    }
    if (options.contains("numberOfBars")) {
        m_numberOfBars->setValue(options.value("numberOfBars").toInt());
    }
    if (options.contains("maximumFrameDelay")) {
        m_maximumFrameDelay->setValue(options.value("maximumFrameDelay").toInt());
    }
    if (options.contains("barKeepsColor")) {
        m_barKeepsColor->setChecked(options.value("barKeepsColor").toBool());
    }
    if (options.contains("blendColor")) {
        m_blendColor->setChecked(options.value("blendColor").toBool());
    }
}

LedWallStudio::ModeOptions MultiBarsOptionsWidget::getOptions() const
{
    LedWallStudio::ModeOptions options;

    options.insert("fadeRate", m_fadeRate->value());
    options.insert("barTravelSpeed", m_barTravelSpeed->value());
    options.insert("numberOfBars", m_numberOfBars->value());
    options.insert("maximumFrameDelay", m_maximumFrameDelay->value());
    options.insert("barKeepsColor", m_barKeepsColor->isChecked());
    options.insert("blendColor", m_blendColor->isChecked());

    return options;
}

void MultiBarsOptionsWidget::initUi()
{
    m_fadeRate = new QSpinBox(this);
    m_fadeRate->setRange(0, 255);

    m_barTravelSpeed = new QSpinBox(this);
    m_barTravelSpeed->setRange(0, 255);

    m_numberOfBars = new QSpinBox(this);
    m_numberOfBars->setRange(1, 10);

    m_maximumFrameDelay = new QSpinBox(this);
    m_maximumFrameDelay->setRange(0, 255);

    m_barKeepsColor = new QCheckBox(tr("Bar keeps color"), this);
    m_blendColor = new QCheckBox(tr("Blend colors of crossing Bars"), this);

    auto layout = new QFormLayout(this);
    layout->addRow(tr("Fade Rate"), m_fadeRate);
    layout->addRow(tr("Bar travel speed"), m_barTravelSpeed);
    layout->addRow(tr("Number of Bars"), m_numberOfBars);
    layout->addRow(tr("Maximum frame delay"), m_maximumFrameDelay);
    layout->addRow(m_barKeepsColor);
    layout->addRow(m_blendColor);
    setLayout(layout);
}
