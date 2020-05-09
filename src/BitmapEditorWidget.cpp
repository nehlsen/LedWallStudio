#include <QtWidgets/QVBoxLayout>
#include <QtCore/QDebug>
#include "BitmapEditorWidget.h"

BitmapEditorWidget::BitmapEditorWidget(QWidget *parent) : QWidget(parent)
{
    m_view = new QGraphicsView(this);

    auto *layout = new QVBoxLayout;
    layout->addWidget(m_view);
    setLayout(layout);

    m_scene = new BitmapEditorCanvas(this);
    m_view->setScene(m_scene);

    connect(m_scene, &BitmapEditorCanvas::bitmapChanged, this, &BitmapEditorWidget::onBitmapChanged);
}

void BitmapEditorWidget::onBitmapChanged()
{
    qDebug() << m_scene->getBitmap();
}
