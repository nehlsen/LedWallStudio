#include "TextOptionsWidget.h"
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QComboBox>

TextOptionsWidget::TextOptionsWidget(QWidget *parent) : ModeOptionsWidget(parent)
{
    initUi();
}

void TextOptionsWidget::setOptions(const LedWallStudio::ModeOptions &options)
{
    if (options.contains("text")) {
        m_text->setText(options.value("text").toString());
    }
    if (options.contains("scrollSpeed")) {
        m_scrollSpeed->setValue(options.value("scrollSpeed").toInt());
    }
    if (options.contains("scrollDirection")) {
        m_scrollDirection->setCurrentIndex(options.value("scrollDirection").toInt());
    }
    if (options.contains("scrollMode")) {
        m_scrollMode->setCurrentIndex(options.value("scrollMode").toInt());
    }
}

LedWallStudio::ModeOptions TextOptionsWidget::getOptions() const
{
    LedWallStudio::ModeOptions options;

    options.insert("text", m_text->text());
    options.insert("scrollSpeed", m_scrollSpeed->value());
    options.insert("scrollDirection", m_scrollDirection->currentIndex());
    options.insert("scrollMode", m_scrollMode->currentIndex());

    return options;
}

void TextOptionsWidget::initUi()
{
    m_text = new QLineEdit(this);
    m_scrollSpeed = new QSpinBox(this);
    m_scrollSpeed->setRange(0, 255);
    m_scrollDirection = new QComboBox(this);
    m_scrollDirection->addItem(tr("Left"));
    m_scrollDirection->addItem(tr("Right"));
    m_scrollMode = new QComboBox(this);
    m_scrollMode->addItem(tr("None"));
    m_scrollMode->addItem(tr("Infinite"));
    m_scrollMode->addItem(tr("Bounce"));

    auto layout = new QFormLayout(this);
    layout->addRow(tr("Text"), m_text);
    layout->addRow(tr("Scroll Speed"), m_scrollSpeed);
    layout->addRow(tr("Scroll Direction"), m_scrollDirection);
    layout->addRow(tr("Scroll Mode"), m_scrollMode);
    setLayout(layout);
}
