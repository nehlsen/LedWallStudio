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
}

LedWallStudio::ModeOptions TextOptionsWidget::getOptions() const
{
    LedWallStudio::ModeOptions options;

    options.insert("text", m_text->text());
    options.insert("scrollSpeed", m_scrollSpeed->value());
    options.insert("scrollDirection", m_scrollDirection->currentIndex());

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

    auto layout = new QFormLayout(this);
    layout->addRow(tr("Text"), m_text);
    layout->addRow(tr("Scroll Speed"), m_scrollSpeed);
    layout->addRow(tr("Scroll Direction"), m_scrollDirection);
    setLayout(layout);
}
