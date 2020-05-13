#include "BitmapFramesWidget.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include "FrameListModel.h"
#include "../BitmapEditor.h"

BitmapFramesWidget::BitmapFramesWidget(BitmapEditor *bitmapEditor, QWidget *parent):
        QWidget(parent), m_bitmapEditor(bitmapEditor)
{
    createUi();
}

void BitmapFramesWidget::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    // save current/deselected frame
    if (!deselected.isEmpty()) {
        m_frames->setBitmap(deselected.indexes().first().row(), m_bitmapEditor->getBitmap());
    }

    // load selected frame
    if (!selected.isEmpty()) {
        m_bitmapEditor->setBitmap(m_frames->getBitmap(selected.indexes().first().row()));
    }

    // disable remove button if no selection
    m_btnRemove->setDisabled(selected.isEmpty());
}

void BitmapFramesWidget::onBtnAddClicked()
{
    m_frames->addFrame();
}

void BitmapFramesWidget::onBtnRemoveClicked()
{
    if (m_view->selectionModel()->selection().isEmpty()) {
        return;
    }

    m_frames->removeRow(m_view->selectionModel()->selection().indexes().first().row());
}

void BitmapFramesWidget::createUi()
{
    auto *layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);

    m_frames = new FrameListModel(this);

    m_view = new QListView(this);
    m_view->setModel(m_frames);
    connect(m_view->selectionModel(), &QItemSelectionModel::selectionChanged, this, &BitmapFramesWidget::onSelectionChanged);
    layout->addWidget(m_view);

    auto *btnLayout = new QHBoxLayout;
    btnLayout->addStretch();
    layout->addLayout(btnLayout);

    m_btnAdd = new QPushButton("+", this);
    connect(m_btnAdd, &QPushButton::clicked, this, &BitmapFramesWidget::onBtnAddClicked);
    btnLayout->addWidget(m_btnAdd);

    m_btnRemove = new QPushButton("-", this);
    connect(m_btnRemove, &QPushButton::clicked, this, &BitmapFramesWidget::onBtnRemoveClicked);
    m_btnRemove->setDisabled(true);
    btnLayout->addWidget(m_btnRemove);

    // TODO play/pause button to send the DELTA frames to the wall in sequence

    setLayout(layout);
}
