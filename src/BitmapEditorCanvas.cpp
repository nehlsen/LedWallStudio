#include "BitmapEditorCanvas.h"
#include <QGraphicsSceneMouseEvent>
#include <QtWidgets/QtWidgets>

BitmapEditorCanvas::BitmapEditorCanvas(QObject *parent) : QGraphicsScene(parent)
{
    setBackgroundBrush(QBrush(Qt::black));
    setSize(5, 5);
}

void BitmapEditorCanvas::setSize(quint32 width, quint32 height)
{
    if (m_width == width && m_height == height) {
        return;
    }

    m_width = width;
    m_height = height;
    clearCanvas();
}

Bitmap BitmapEditorCanvas::getBitmap() const
{
    Bitmap bitmap = Bitmap();

    for (int x = 0; x < m_width; ++x) {
        for (int y = 0; y < m_height; ++y) {
            QPointF pos = QPointF(x * m_gridSize + m_gridSize / 2, y * m_gridSize + m_gridSize / 2);
            QList<QGraphicsItem*> itemsAtPos = items(pos);
            if (itemsAtPos.size() == 1) {
                QGraphicsItem *itm = itemsAtPos.first();
                auto *rect = qgraphicsitem_cast<QGraphicsRectItem *>(itm);
                bitmap.insert(QPoint(x, m_height - 1 - y), rect->brush().color());
            }
        }
    }

    return bitmap;
}

void BitmapEditorCanvas::drawGrid()
{
    for (int x = 0; x < m_width; ++x) {
        for (int y = 0; y < m_height; ++y) {
            addRect(x * m_gridSize, y * m_gridSize, m_gridSize, m_gridSize, QPen(Qt::white), QBrush(Qt::black));
        }
    }
}

void BitmapEditorCanvas::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() != Qt::LeftButton && event->button() != Qt::RightButton) {
        return;
    }

    QList<QGraphicsItem*> itemsAtPos = items(event->scenePos());
    if (itemsAtPos.size() != 1) {
        return;
    }

    auto *rect = qgraphicsitem_cast<QGraphicsRectItem*>(itemsAtPos.first());
    if (rect == nullptr) {
        return;
    }

    if (event->button() == Qt::LeftButton && rect->brush() != m_primaryColor) {
        rect->setBrush(QBrush(m_primaryColor));
        rect->update();
        emit bitmapChanged();
    } else if (event->button() == Qt::RightButton && rect->brush() != m_secondaryColor) {
        rect->setBrush(QBrush(m_secondaryColor));
        rect->update();
        emit bitmapChanged();
    }
}

const QColor &BitmapEditorCanvas::getPrimaryColor() const
{
    return m_primaryColor;
}

void BitmapEditorCanvas::setPrimaryColor(const QColor &primaryColor)
{
    m_primaryColor = primaryColor;
}

const QColor &BitmapEditorCanvas::getSecondaryColor() const
{
    return m_secondaryColor;
}

void BitmapEditorCanvas::setSecondaryColor(const QColor &secondaryColor)
{
    m_secondaryColor = secondaryColor;
}

void BitmapEditorCanvas::clearCanvas()
{
    clear();
    drawGrid();

    emit bitmapChanged();
}
