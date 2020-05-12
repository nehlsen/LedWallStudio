#include "ModeConfigWidget.h"
#include "../HttpConnector/HttpConnector.h"
#include <QtWidgets/QComboBox>
#include <QtWidgets/QVBoxLayout>
#include "ModesListModel.h"

ModeConfigWidget::ModeConfigWidget(HttpConnector *httpConnector, QWidget *parent):
    QWidget(parent), m_httpConnector(httpConnector)
{
    createUi();
    connect(m_httpConnector, &HttpConnector::connectionStatusChanged, this, &ModeConfigWidget::setEnabled);
    connect(m_httpConnector, &HttpConnector::activeModeChanged, this, &ModeConfigWidget::onActiveModeChanged);
}

void ModeConfigWidget::onActiveModeChanged()
{
    // TODO update mode config
}

void ModeConfigWidget::createUi()
{
    m_selectMode = new QComboBox;
    m_selectMode->setModel(new ModesListModel(m_httpConnector, this));

    auto *layout = new QVBoxLayout;
    layout->addWidget(m_selectMode);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
}
