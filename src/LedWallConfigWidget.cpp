#include <QtWidgets/QFormLayout>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QPushButton>
#include "LedWallConfigWidget.h"
#include "HttpConnector/HttpConnector.h"

LedWallConfigWidget::LedWallConfigWidget(HttpConnector *httpConnector, QWidget *parent):
    QWidget(parent), m_httpConnector(httpConnector)
{
    createUi();
    connect(m_httpConnector, &HttpConnector::connected, this, &LedWallConfigWidget::loadConfig);
}

void LedWallConfigWidget::loadConfig()
{
    m_editBrightness->setValue(m_httpConnector->getConfig().Brightness);
}

void LedWallConfigWidget::saveConfig()
{
    auto cfg = m_httpConnector->getConfig();
    cfg.Brightness = m_editBrightness->value();

    m_httpConnector->setConfig(cfg);
}

void LedWallConfigWidget::createUi()
{
    auto *layout = new QFormLayout;
    m_editBrightness = new QSpinBox;
    m_editBrightness->setRange(0, 255);
    layout->addRow(tr("Brightness"), m_editBrightness);

    auto *btnSave = new QPushButton;
    btnSave->setText(tr("Save"));
    connect(btnSave, &QPushButton::clicked, this, &LedWallConfigWidget::saveConfig);
    layout->addRow(btnSave);

    setLayout(layout);
}
