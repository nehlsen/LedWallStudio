#include "BitmapEditor.h"
#include <QGraphicsSceneMouseEvent>
#include <QtWidgets/QtWidgets>

BitmapEditor::BitmapEditor(QWidget *parent):
    QGraphicsView(parent)
{
    m_scene = new QGraphicsScene(this);
    setScene(m_scene);
    setBackgroundBrush(QBrush(Qt::black));
    setSize(5, 5);
}

void BitmapEditor::setSize(quint32 width, quint32 height)
{
    if (m_width == width && m_height == height) {
        return;
    }

    m_width = width;
    m_height = height;
    clearCanvas();
}

const QColor &BitmapEditor::getPrimaryColor() const
{
    return m_primaryColor;
}

void BitmapEditor::setPrimaryColor(const QColor &primaryColor)
{
    m_primaryColor = primaryColor;
}

const QColor &BitmapEditor::getSecondaryColor() const
{
    return m_secondaryColor;
}

void BitmapEditor::setSecondaryColor(const QColor &secondaryColor)
{
    m_secondaryColor = secondaryColor;
}

Bitmap BitmapEditor::getBitmap() const
{
    Bitmap bitmap = Bitmap();
    for (int x = 0; x < m_width; ++x) {
        for (int y = 0; y < m_height; ++y) {
            QList<QGraphicsItem*> itemsAtPos = items(gridToViewCoordinates({x, y}));
            if (itemsAtPos.size() != 1) {
                continue;
            }

            auto *rect = qgraphicsitem_cast<QGraphicsRectItem*>(itemsAtPos.first());
            bitmap.insert({x, (int)m_height - 1 - y}, rect->brush().color());
        }
    }

    return bitmap;
}

void BitmapEditor::setBitmap(const Bitmap& bitmap)
{
    m_scene->clear();
    drawGrid();
    QMapIterator<QPoint, QColor> mi(bitmap);
    while (mi.hasNext()) {
        mi.next();
        QList<QGraphicsItem*> itemsAtPos = items(gridToViewCoordinates({mi.key().x(), (int) m_height - 1 - mi.key().y()}));
        if (itemsAtPos.size() != 1) {
            continue;
        }
        auto *rect = qgraphicsitem_cast<QGraphicsRectItem*>(itemsAtPos.first());
        rect->setBrush(mi.value());
    }
    emit bitmapChanged();
}

void BitmapEditor::clearCanvas()
{
    m_scene->clear();
    drawGrid();

    emit bitmapChanged();
}

void BitmapEditor::drawGrid()
{
    for (int x = 0; x < m_width; ++x) {
        for (int y = 0; y < m_height; ++y) {
            m_scene->addRect(x * m_gridSize, y * m_gridSize, m_gridSize, m_gridSize, QPen(Qt::white), QBrush(Qt::black));
        }
    }
}

QPoint BitmapEditor::viewToGridCoordinates(const QPoint &viewCoordinates) const
{
    auto sceneCoordinates = mapToScene(viewCoordinates);
    return {(int)(sceneCoordinates.x() / m_gridSize), (int)(sceneCoordinates.y() / m_gridSize)};
}

QPoint BitmapEditor::gridToViewCoordinates(const QPoint &gridCoordinates) const
{
    return mapFromScene({gridCoordinates.x() * m_gridSize + m_gridSize / 2, gridCoordinates.y() * m_gridSize + m_gridSize / 2});
}

void BitmapEditor::mouseReleaseEvent(QMouseEvent *event)
{
    if (paintAction(event)) {
        event->accept();
    }
}

void BitmapEditor::mouseMoveEvent(QMouseEvent *event)
{
    if (paintAction(event)) {
        event->accept();
    }
}

bool BitmapEditor::paintAction(QMouseEvent *event)
{
    QList<QGraphicsItem*> itemsAtPos = items(event->pos());
    if (itemsAtPos.size() != 1) {
        return false;
    }

    auto *rect = qgraphicsitem_cast<QGraphicsRectItem*>(itemsAtPos.first());
    if (rect == nullptr) {
        return false;
    }

    if ((event->button() == Qt::LeftButton || event->buttons() & Qt::LeftButton) && rect->brush() != m_primaryColor) {
        rect->setBrush(QBrush(m_primaryColor));
        emit bitmapChanged();
        emit bitmapChanged(viewToGridCoordinates(event->pos()));
    } else if ((event->button() == Qt::RightButton || event->buttons() & Qt::RightButton) && rect->brush() != m_secondaryColor) {
        rect->setBrush(QBrush(m_secondaryColor));
        emit bitmapChanged();
        emit bitmapChanged(viewToGridCoordinates(event->pos()));
    } else {
        return false;
    }

    return true;
}
