#ifndef LEDWALLSTUDIO_GRIDHEXAGON_H
#define LEDWALLSTUDIO_GRIDHEXAGON_H

#include "Grid.h"

class GridHexagon : public Grid
{
public:
    using Grid::Grid;

    void drawGrid() override;

    QPoint sceneToGridCoordinates(const QPointF &sceneCoordinates) const override;
    QPointF gridToSceneCoordinates(const QPoint &gridCoordinates) const override;

protected:
    const qreal m_factor = 1.5;
    const qreal m_width = 14 * m_factor;
    const qreal m_height = 16 * m_factor;

    void drawCell(int gridX, int gridY);
};

#endif //LEDWALLSTUDIO_GRIDHEXAGON_H
