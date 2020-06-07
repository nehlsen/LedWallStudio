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
    qWarning("NOT IMPLEMENTED - GridHexagon::sceneToGridCoordinates");
    return QPoint();
}

QPointF GridHexagon::gridToSceneCoordinates(const QPoint &gridCoordinates) const
{
    return {
        gridCoordinates.x() * m_width + (gridCoordinates.y() % 2 == 1 ? (m_width/2.0) : 0),
        gridCoordinates.y() * (0.75 * m_height)
    };
}

void GridHexagon::drawCell(int gridX, int gridY)
{
    QPolygonF cellPoints;
    cellPoints << QPointF((m_width/2.0), (m_height/4.0));
    cellPoints << QPointF((m_width/2.0), -(m_height/4.0));
    cellPoints << QPointF(0, -(m_height/2.0));
    cellPoints << QPointF(-(m_width/2.0), -(m_height/4.0));
    cellPoints << QPointF(-(m_width/2.0), (m_height/4.0));
    cellPoints << QPointF(0, (m_height/2.0));

    auto cell = new QGraphicsPolygonItem(cellPoints);
    cell->setPen(m_lineColor);
    cell->setBrush(m_backgroundColor);
    cell->moveBy(
            gridX * m_width + (gridY % 2 == 1 ? (m_width/2.0) : 0),
            gridY * (0.75 * m_height)
            );
    m_scene->addItem(cell);
}
