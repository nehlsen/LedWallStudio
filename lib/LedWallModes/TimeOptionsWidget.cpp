#include "TimeOptionsWidget.h"
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QFormLayout>

TimeOptionsWidget::TimeOptionsWidget(QWidget *parent):
    TextOptionsWidget(parent)
{
    initUi();
}

void TimeOptionsWidget::setOptions(const LedWallStudio::ModeOptions &options)
{
    TextOptionsWidget::setOptions(options);

    if (options.contains("variant")) {
        m_variant->setCurrentIndex(options.value("variant").toInt());
    }
    if (options.contains("parameter")) {
        m_variantParameter->setValue(options.value("parameter").toInt());
    }
}

LedWallStudio::ModeOptions TimeOptionsWidget::getOptions() const
{
    auto options = TextOptionsWidget::getOptions();

    options.insert("variant", m_variant->currentIndex());
    options.insert("parameter", m_variantParameter->value());

    return options;
}

void TimeOptionsWidget::initUi()
{
    m_text->setEnabled(false);

    m_variant = new QComboBox(this);
    m_variant->addItem(tr("Time"));
    m_variant->addItem(tr("CountDown"));
    m_variant->addItem(tr("CountDownTo"));
    m_variant->addItem(tr("CountUp"));
    m_variant->addItem(tr("CountSince"));
    m_variantParameter = new QSpinBox(this);
    m_variantParameter->setRange(0, 60 * 60 * 24);

    auto l = dynamic_cast<QFormLayout*>(layout());
    l->addRow(tr("Variant"), m_variant);
    l->addRow(tr("Variant Parameter"), m_variantParameter);
}
