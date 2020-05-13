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
            QList<QGraphicsItem*> itemsAtPos = items(gridToSceneCoordinates({x, y}));
            if (itemsAtPos.size() != 1) {
                continue;
            }

            auto *rect = qgraphicsitem_cast<QGraphicsRectItem*>(itemsAtPos.first());
            bitmap.insert({x, (int)m_height - 1 - y}, rect->brush().color());
        }
    }

    return bitmap;
}

void BitmapEditorCanvas::setBitmap(const Bitmap& bitmap)
{
    clear();
    drawGrid();
    QMapIterator<QPoint, QColor> mi(bitmap);
    while (mi.hasNext()) {
        mi.next();
        QList<QGraphicsItem*> itemsAtPos = items(gridToSceneCoordinates({mi.key().x(), (int) m_height - 1 - mi.key().y()}));
        if (itemsAtPos.size() != 1) {
            continue;
        }
        auto *rect = qgraphicsitem_cast<QGraphicsRectItem*>(itemsAtPos.first());
        rect->setBrush(mi.value());
    }
    emit bitmapChanged();
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
        emit bitmapChanged(sceneToGridCoordinates(event->scenePos()));
    } else if (event->button() == Qt::RightButton && rect->brush() != m_secondaryColor) {
        rect->setBrush(QBrush(m_secondaryColor));
        rect->update();
        emit bitmapChanged();
        emit bitmapChanged(sceneToGridCoordinates(event->scenePos()));
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

QPoint BitmapEditorCanvas::sceneToGridCoordinates(const QPointF &sceneCoordinates) const
{
    return {(int)(sceneCoordinates.x() / m_gridSize), (int)(sceneCoordinates.y() / m_gridSize)};
}

QPointF BitmapEditorCanvas::gridToSceneCoordinates(const QPoint &gridCoordinates) const
{
    return {gridCoordinates.x() * m_gridSize + m_gridSize / 2, gridCoordinates.y() * m_gridSize + m_gridSize / 2};
}

void BitmapEditorCanvas::clearCanvas()
{
    clear();
    drawGrid();

    emit bitmapChanged();
}
