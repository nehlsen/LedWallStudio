#include "BitmapEditor.h"
#include "GridRect.h"
#include "GridHexagon.h"
#include <QGraphicsSceneMouseEvent>
#include <QtWidgets/QtWidgets>
#include <QtCore/QDebug>

BitmapEditor::BitmapEditor(QWidget *parent): BitmapEditor(GridModeRect, parent)
{}

BitmapEditor::BitmapEditor(BitmapEditor::GridMode gridMode, QWidget *parent):
    QGraphicsView(parent)
{
    m_scene = new QGraphicsScene(this);
    setScene(m_scene);
    setBackgroundBrush(QBrush(Qt::black));

    if (gridMode == GridModeHexagon) {
        m_grid = new GridHexagon(m_scene);
    } else {
        m_grid = new GridRect(m_scene);
    }

    setSize({5, 5});
}

void BitmapEditor::setSize(quint32 width, quint32 height)
{
    setSize(QSize(width, height));
}

QSize BitmapEditor::getGridSize() const
{
    return m_grid->getSize();
}

void BitmapEditor::setGridSize(const QSize &size)
{
    if (m_grid->getSize() == size) {
        return;
    }

    m_grid->setSize(size);
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
    for (int x = 0; x < getSize().width(); ++x) {
        for (int y = 0; y < getSize().height(); ++y) {
            QList<QGraphicsItem*> itemsAtPos = items(gridToViewCoordinates({x, y}));
            if (itemsAtPos.size() != 1) {
                continue;
            }

            auto *gridCell = qgraphicsitem_cast<QAbstractGraphicsShapeItem*>(itemsAtPos.first());
            if (gridCell != nullptr) {
                bitmap.insert({x, getSize().height() - 1 - y}, gridCell->brush().color());
            }
        }
    }

    return bitmap;
}

void BitmapEditor::setBitmap(const Bitmap& bitmap)
{
//    qDebug() << "BitmapEditor::setBitmap\n" << bitmap;

    clearCanvas();

    QMapIterator<QPoint, QColor> mi(bitmap);
    while (mi.hasNext()) {
        mi.next();
        QList<QGraphicsItem*> itemsAtPos = items(gridToViewCoordinates({mi.key().x(), getSize().height() - 1 - mi.key().y()}));
        if (itemsAtPos.size() != 1) {
            continue;
        }

        auto *gridCell = qgraphicsitem_cast<QAbstractGraphicsShapeItem*>(itemsAtPos.first());
        if (gridCell != nullptr) {
            gridCell->setBrush(mi.value());
        }
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
    m_grid->drawGrid();
}

QPoint BitmapEditor::viewToGridCoordinates(const QPoint &viewCoordinates) const
{
    auto sceneCoordinates = mapToScene(viewCoordinates);
    return m_grid->sceneToGridCoordinates(sceneCoordinates);
}

QPoint BitmapEditor::gridToViewCoordinates(const QPoint &gridCoordinates) const
{
    return mapFromScene(m_grid->gridToSceneCoordinates(gridCoordinates));
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

    auto *gridCell = qgraphicsitem_cast<QAbstractGraphicsShapeItem*>(itemsAtPos.first());
    if (gridCell == nullptr) {
        return false;
    }

    if ((event->button() == Qt::LeftButton || event->buttons() & Qt::LeftButton) && gridCell->brush() != m_primaryColor) {
        gridCell->setBrush(QBrush(m_primaryColor));
        emit bitmapChanged();
        emit bitmapChanged(viewToGridCoordinates(event->pos()));
    } else if ((event->button() == Qt::RightButton || event->buttons() & Qt::RightButton) && gridCell->brush() != m_secondaryColor) {
        gridCell->setBrush(QBrush(m_secondaryColor));
        emit bitmapChanged();
        emit bitmapChanged(viewToGridCoordinates(event->pos()));
    } else {
        return false;
    }

    return true;
}
