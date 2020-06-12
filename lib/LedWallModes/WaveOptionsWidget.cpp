#include "WaveOptionsWidget.h"
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>

WaveOptionsWidget::WaveOptionsWidget(QWidget *parent):
    ModeOptionsWidget(parent)
{
    initUi();
}

void WaveOptionsWidget::initUi()
{
    m_waveMode = new QComboBox(this);
    m_waveMode->addItem(tr("Horizontal"), 0);
    m_waveMode->addItem(tr("Vertical"), 1);
    m_waveMode->addItem(tr("Radial Circle"), 2);
    m_waveMode->addItem(tr("Radial Rect"), 3);

    m_waveDirection = new QComboBox(this);
    m_waveDirection->addItem(tr("Forward"), 0);
    m_waveDirection->addItem(tr("Reverse"), 1);

    m_waveLength = new QSpinBox(this);
    m_waveLength->setRange(0, 250);

    m_speed = new QSpinBox(this);
    m_speed->setRange(0, 250);

    m_colorHueMin = new QSpinBox(this);
    m_colorHueMin->setRange(0, 255);
    m_colorHueMax = new QSpinBox(this);
    m_colorHueMax->setRange(0, 255);
    auto *rowHue = new QHBoxLayout;
    rowHue->addWidget(m_colorHueMin);
    rowHue->addWidget(m_colorHueMax);

    m_colorSaturationMin = new QSpinBox(this);
    m_colorSaturationMin->setRange(0, 255);
    m_colorSaturationMax = new QSpinBox(this);
    m_colorSaturationMax->setRange(0, 255);
    auto *rowSaturation = new QHBoxLayout;
    rowSaturation->addWidget(m_colorSaturationMin);
    rowSaturation->addWidget(m_colorSaturationMax);

    m_colorValueMin = new QSpinBox(this);
    m_colorValueMin->setRange(0, 255);
    m_colorValueMax = new QSpinBox(this);
    m_colorValueMax->setRange(0, 255);
    auto *rowValue = new QHBoxLayout;
    rowValue->addWidget(m_colorValueMin);
    rowValue->addWidget(m_colorValueMax);

    auto layout = new QFormLayout(this);
    layout->addRow(tr("Wave Mode"), m_waveMode);
    layout->addRow(tr("Wave Direction"), m_waveDirection);
    layout->addRow(tr("Wave Length"), m_waveLength);
    layout->addRow(tr("Speed"), m_speed);
    layout->addRow(tr("Hue"), rowHue);
    layout->addRow(tr("Saturation"), rowSaturation);
    layout->addRow(tr("Value"), rowValue);
    setLayout(layout);
}

void WaveOptionsWidget::setOptions(const LedWallStudio::ModeOptions &options)
{
    if (options.contains("waveMode")) {
        m_waveMode->setCurrentIndex(options.value("waveMode").toInt());
    }
    if (options.contains("waveDirection")) {
        m_waveDirection->setCurrentIndex(options.value("waveDirection").toInt());
    }
    if (options.contains("waveLength")) {
        m_waveLength->setValue(options.value("waveLength").toInt());
    }
    if (options.contains("speed")) {
        m_speed->setValue(options.value("speed").toInt());
    }

    if (options.contains("colorHueLow")) {
        m_colorHueMin->setValue(options.value("colorHueLow").toInt());
    }
    if (options.contains("colorHueHigh")) {
        m_colorHueMax->setValue(options.value("colorHueHigh").toInt());
    }
    if (options.contains("colorSaturationLow")) {
        m_colorSaturationMin->setValue(options.value("colorSaturationLow").toInt());
    }
    if (options.contains("colorSaturationHigh")) {
        m_colorSaturationMax->setValue(options.value("colorSaturationHigh").toInt());
    }
    if (options.contains("colorValueLow")) {
        m_colorValueMin->setValue(options.value("colorValueLow").toInt());
    }
    if (options.contains("colorValueHigh")) {
        m_colorValueMax->setValue(options.value("colorValueHigh").toInt());
    }
}

LedWallStudio::ModeOptions WaveOptionsWidget::getOptions() const
{
    LedWallStudio::ModeOptions options;

    options.insert("waveMode", m_waveMode->currentIndex());
    options.insert("waveDirection", m_waveDirection->currentIndex());
    options.insert("waveLength", m_waveLength->value());
    options.insert("speed", m_speed->value());

    options.insert("colorHueLow", m_colorHueMin->value());
    options.insert("colorHueHigh", m_colorHueMax->value());
    options.insert("colorSaturationLow", m_colorSaturationMin->value());
    options.insert("colorSaturationHigh", m_colorSaturationMax->value());
    options.insert("colorValueLow", m_colorValueMin->value());
    options.insert("colorValueHigh", m_colorValueMax->value());

    return options;
}
