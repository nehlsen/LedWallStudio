#ifndef LEDWALLSTUDIO_GRIDRECT_H
#define LEDWALLSTUDIO_GRIDRECT_H

#include "Grid.h"

class GridRect : public Grid
{
public:
    using Grid::Grid;

    void drawGrid() override;

    QPoint sceneToGridCoordinates(const QPointF &sceneCoordinates) const override;
    QPointF gridToSceneCoordinates(const QPoint &gridCoordinates) const override;

protected:
    const qreal m_gridWidth = 20; // width of one cell
    const qreal m_gridHeight = 20; // height of one cell
};

#endif //LEDWALLSTUDIO_GRIDRECT_H
