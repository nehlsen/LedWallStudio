#include "FancyScriptOptionsWidget.h"
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QVBoxLayout>

FancyScriptOptionsWidget::FancyScriptOptionsWidget(QWidget *parent) : ModeOptionsWidget(parent)
{
    initUi();
}

void FancyScriptOptionsWidget::setOptions(const LedWallStudio::ModeOptions &options)
{
    if (options.contains("script")) {
        m_script->setPlainText(options.value("script").toString());
    }
}

LedWallStudio::ModeOptions FancyScriptOptionsWidget::getOptions() const
{
    LedWallStudio::ModeOptions options;

    options.insert("script", m_script->toPlainText());

    return options;
}

void FancyScriptOptionsWidget::initUi()
{
    m_script = new QPlainTextEdit(this);
    m_script->setPlainText("");

    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_script);
    setLayout(layout);
}
