#include "ModeConfigWidget.h"
#include "../WallController/WallController.h"
#include <QtWidgets/QComboBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include "ModesListModel.h"
#include "ModeOptionsWidget.h"
#include "WaveOptionsWidget.h"
#include "MultiBarsOptionsWidget.h"

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

    if (m_modeOptionsWidget != nullptr) {
        m_btnSetOptions->setEnabled(false);
        layout()->removeWidget(m_modeOptionsWidget);
        delete m_modeOptionsWidget;
        m_modeOptionsWidget = nullptr;
    }

    if (m_wallController->getMode().Name == "Wave") {
        m_modeOptionsWidget = new WaveOptionsWidget(this);
        m_modeOptionsWidget->setOptions(m_wallController->getMode().Options);
        layout()->addWidget(m_modeOptionsWidget);
        m_btnSetOptions->setEnabled(true);
    } else if (m_wallController->getMode().Name == "MultiBars") {
        m_modeOptionsWidget = new MultiBarsOptionsWidget(this);
        m_modeOptionsWidget->setOptions(m_wallController->getMode().Options);
        layout()->addWidget(m_modeOptionsWidget);
        m_btnSetOptions->setEnabled(true);
    }
}

void ModeConfigWidget::onSetModeClicked()
{
    m_wallController->setModeByIndex(m_selectMode->currentData().toInt());
}

void ModeConfigWidget::onSetOptionsClicked()
{
    if (m_modeOptionsWidget == nullptr) {
        return;
    }

    m_wallController->setModeOptions(m_modeOptionsWidget->getOptions());
}

void ModeConfigWidget::createUi()
{
    m_selectMode = new QComboBox;
    m_selectMode->setModel(new ModesListModel(m_wallController, this));

    auto *btnSetMode = new QPushButton(tr("Set Mode"), this);
    connect(btnSetMode, &QPushButton::clicked, this, &ModeConfigWidget::onSetModeClicked);

    m_btnSetOptions = new QPushButton(tr("Set Options"), this);
    m_btnSetOptions->setEnabled(false);
    connect(m_btnSetOptions, &QPushButton::clicked, this, &ModeConfigWidget::onSetOptionsClicked);

    auto *layout = new QVBoxLayout;
    layout->addWidget(m_selectMode);
    layout->addWidget(btnSetMode);
    layout->addWidget(m_btnSetOptions);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
}
