#include "GridRect.h"

void GridRect::drawGrid()
{
    for (int x = 0; x < m_size.width(); ++x) {
        for (int y = 0; y < m_size.height(); ++y) {
            m_scene->addRect(x * m_gridWidth, y * m_gridHeight, m_gridWidth, m_gridHeight, m_lineColor, m_backgroundColor);
        }
    }
}

QPoint GridRect::sceneToGridCoordinates(const QPointF &sceneCoordinates) const
{
    return {(int)(sceneCoordinates.x() / m_gridWidth), (int)(sceneCoordinates.y() / m_gridHeight)};
}

QPointF GridRect::gridToSceneCoordinates(const QPoint &gridCoordinates) const
{
    return {gridCoordinates.x() * m_gridWidth + m_gridWidth / 2, gridCoordinates.y() * m_gridHeight + m_gridHeight / 2};
}
