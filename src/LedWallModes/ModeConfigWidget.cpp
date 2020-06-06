#include "ModeConfigWidget.h"
#include "../WallController/WallController.h"
#include <QtWidgets/QComboBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include "ModesListModel.h"

ModeConfigWidget::ModeConfigWidget(WallController *wallController, QWidget *parent):
    QWidget(parent), m_wallController(wallController)
{
    createUi();
    connect(m_wallController, &WallController::connectionStatusChanged, this, &ModeConfigWidget::setEnabled);
    connect(m_wallController, &WallController::modeChanged, this, &ModeConfigWidget::onModeChanged);
}

void ModeConfigWidget::onModeChanged()
{
    // TODO update mode config
    int newComboIndex = -1;
    auto model = qobject_cast<ModesListModel*>(m_selectMode->model());
    if (model) {
        newComboIndex = model->modeIndexToModelIndex(m_wallController->getMode().Index).row();
    }

    m_selectMode->setCurrentIndex(newComboIndex);
}

void ModeConfigWidget::onSetModeClicked()
{
    m_wallController->setModeByIndex(m_selectMode->currentData().toInt());
}

void ModeConfigWidget::createUi()
{
    m_selectMode = new QComboBox;
    m_selectMode->setModel(new ModesListModel(m_wallController, this));

    auto *btnSetMode = new QPushButton(tr("Set Mode"), this);
    connect(btnSetMode, &QPushButton::clicked, this, &ModeConfigWidget::onSetModeClicked);

    auto *layout = new QVBoxLayout;
    layout->addWidget(m_selectMode);
    layout->addWidget(btnSetMode);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
}
