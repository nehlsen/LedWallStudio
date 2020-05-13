#include "ModeConfigWidget.h"
#include "../HttpConnector/HttpConnector.h"
#include <QtWidgets/QComboBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include "ModesListModel.h"

ModeConfigWidget::ModeConfigWidget(HttpConnector *httpConnector, QWidget *parent):
    QWidget(parent), m_httpConnector(httpConnector)
{
    createUi();
    connect(m_httpConnector, &HttpConnector::connectionStatusChanged, this, &ModeConfigWidget::setEnabled);
    connect(m_httpConnector, &HttpConnector::modeChanged, this, &ModeConfigWidget::onModeChanged);
}

void ModeConfigWidget::onModeChanged()
{
    // TODO update mode config
    int newComboIndex = -1;
    auto model = qobject_cast<ModesListModel*>(m_selectMode->model());
    if (model) {
        newComboIndex = model->modeIndexToModelIndex(m_httpConnector->getMode().Index).row();
    }

    m_selectMode->setCurrentIndex(newComboIndex);
}

void ModeConfigWidget::onSetModeClicked()
{
    m_httpConnector->setMode(m_selectMode->currentData().toInt());
}

void ModeConfigWidget::createUi()
{
    m_selectMode = new QComboBox;
    m_selectMode->setModel(new ModesListModel(m_httpConnector, this));

    auto *btnSetMode = new QPushButton(tr("Set Mode"), this);
    connect(btnSetMode, &QPushButton::clicked, this, &ModeConfigWidget::onSetModeClicked);

    auto *layout = new QVBoxLayout;
    layout->addWidget(m_selectMode);
    layout->addWidget(btnSetMode);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
}
