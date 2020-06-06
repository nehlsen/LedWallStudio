#include "GridHexagon.h"

#include <QtWidgets/QGraphicsPolygonItem>

/*
 *https://biancahoegel.de/geometrie/ebene/sechseck.html
 *
 * Koordinaten eines liegenden Sechsecks
P1 (4|7), P3 (8|0), P5 (4|−7), P7 (−4|−7), P9 (−8|0), P11 (−4|7)


Koordinaten eines auf der Spitze stehenden Sechsecks
P2 (7|4), P4 (7|−4), P6 (0|−8), P8 (−7|−4), P10 (−7|4), P12 (0|8)
 *
 */

void GridHexagon::drawGrid()
{
    for (int x = 0; x < m_size.width(); ++x) {
        for (int y = 0; y < m_size.height(); ++y) {
            drawCell(x, y);

        }
    }
}

QPoint GridHexagon::sceneToGridCoordinates(const QPointF &sceneCoordinates) const
{
    return QPoint();
}

QPointF GridHexagon::gridToSceneCoordinates(const QPoint &gridCoordinates) const
{
    const qreal factor = 1.5;

    return {
        gridCoordinates.x() * 2 * 7 * factor + (gridCoordinates.y() % 2 == 1 ? (7 * factor) : 0)
        + (7*factor),
        gridCoordinates.y() * 1.5 * 8 * factor
        + (8*factor)
    };
}

void GridHexagon::drawCell(int gridX, int gridY)
{
    const qreal factor = 1.5;

    QPolygonF p;
    p << QPointF( 7 * factor,  4 * factor);
    p << QPointF( 7 * factor, -4 * factor);
    p << QPointF( 0 * factor, -8 * factor);
    p << QPointF(-7 * factor, -4 * factor);
    p << QPointF(-7 * factor,  4 * factor);
    p << QPointF( 0 * factor,  8 * factor);

    auto i2 = new QGraphicsPolygonItem(p);
    i2->setPen(m_lineColor);
    i2->setBrush(m_backgroundColor);
    i2->moveBy(
            gridX * 2 * 7 * factor + (gridY % 2 == 1 ? (7 * factor) : 0),
            gridY * 1.5 * 8 * factor
            );
    m_scene->addItem(i2);
}
