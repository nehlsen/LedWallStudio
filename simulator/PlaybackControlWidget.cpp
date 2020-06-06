#include "PlaybackControlWidget.h"
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QHBoxLayout>
#include "Simulator.h"

PlaybackControlWidget::PlaybackControlWidget(Simulator *simulator, QWidget *parent):
    QWidget(parent), m_simulator(simulator)
{
    createUi();
}

void PlaybackControlWidget::onSpinFpsChanged(int fps)
{
    if (fps == 0) {
        m_simulator->revertFrameDelay();
    } else {
        m_simulator->setFrameDelay(1000/fps);
    }
}

void PlaybackControlWidget::onButtonStartStopToggled(bool checked)
{
    if (checked) {
        m_simulator->start();
    } else {
        m_simulator->stop();
    }
}

void PlaybackControlWidget::onButtonStepClicked()
{
    m_simulator->step();
}

void PlaybackControlWidget::createUi()
{
    auto *lblFps = new QLabel(tr("fps"));
    auto *spinFps = new QSpinBox();
    lblFps->setBuddy(spinFps);
    spinFps->setRange(0, 40);
    spinFps->setWrapping(true);
    spinFps->setSpecialValueText(tr("Auto"));
    connect(spinFps, QOverload<int>::of(&QSpinBox::valueChanged), this, &PlaybackControlWidget::onSpinFpsChanged);

    auto *btnStartStop = new QPushButton(tr("Start/Stop"));
    btnStartStop->setCheckable(true);
    connect(btnStartStop, &QPushButton::toggled, this, &PlaybackControlWidget::onButtonStartStopToggled);
    auto *btnStep = new QPushButton(tr("Step"));
    connect(btnStartStop, &QPushButton::toggled, btnStep, &QPushButton::setDisabled);
    connect(btnStep, &QPushButton::clicked, this, &PlaybackControlWidget::onButtonStepClicked);

    auto *rowFps = new QHBoxLayout;
    rowFps->addWidget(lblFps);
    rowFps->addWidget(spinFps);
    auto *rowBtns = new QHBoxLayout;
    rowBtns->addWidget(btnStartStop);
    rowBtns->addWidget(btnStep);
    auto *layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addLayout(rowFps);
    layout->addLayout(rowBtns);
    setLayout(layout);
}
