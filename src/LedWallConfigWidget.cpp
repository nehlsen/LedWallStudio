#include "LedWallConfigWidget.h"
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLineEdit>
#include "HttpConnector/HttpConnector.h"

LedWallConfigWidget::LedWallConfigWidget(HttpConnector *httpConnector, QWidget *parent):
    QWidget(parent), m_httpConnector(httpConnector)
{
    createUi();
    connect(m_httpConnector, &HttpConnector::connectionStatusChanged, this, &LedWallConfigWidget::setEnabled);
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

    m_editMatrixWidth = new QSpinBox;
    m_editMatrixWidth->setRange(0, 255);
    layout->addRow(tr("Matrix Width"), m_editMatrixWidth);

    m_editMatrixHeight = new QSpinBox;
    m_editMatrixHeight->setRange(0, 255);
    layout->addRow(tr("Matrix Height"), m_editMatrixHeight);

    m_editBrightness = new QSpinBox;
    m_editBrightness->setRange(0, 255);
    layout->addRow(tr("Brightness"), m_editBrightness);

    m_comboPowerOnResetMode = new QComboBox;
    m_comboPowerOnResetMode->addItem(tr("Always Off"), LedWall::Config::ALWAYS_OFF);
    m_comboPowerOnResetMode->addItem(tr("Always On"), LedWall::Config::ALWAYS_ON);
    m_comboPowerOnResetMode->addItem(tr("Recover Last"), LedWall::Config::RECOVER_LAST);
    layout->addRow(tr("Power on Reset"), m_comboPowerOnResetMode);

    m_checkRecoverLastMode = new QCheckBox(tr("Recover Last"));
    m_comboModeToBootInto = new QComboBox; // TODO fill with available modes
    connect(m_checkRecoverLastMode, &QCheckBox::toggled, m_comboModeToBootInto, &QComboBox::setDisabled);
    auto *layoutBootMode = new QVBoxLayout;
    layoutBootMode->addWidget(m_checkRecoverLastMode);
    layoutBootMode->addWidget(m_comboModeToBootInto);
    layout->addRow(tr("Mode to Boot into"), layoutBootMode);

    m_editMqttBroker = new QLineEdit;
    layout->addRow(tr("MQTT Broker"), m_editMqttBroker);

    m_editMqttDeviceTopic = new QLineEdit;
    layout->addRow(tr("MQTT Device Topic"), m_editMqttDeviceTopic);

    m_editMqttGroupTopic = new QLineEdit;
    layout->addRow(tr("MQTT Group Topic"), m_editMqttGroupTopic);

    auto *btnSave = new QPushButton;
    btnSave->setText(tr("Save"));
    connect(btnSave, &QPushButton::clicked, this, &LedWallConfigWidget::saveConfig);
    layout->addRow(btnSave);

    setLayout(layout);
}