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
    void drawCell(int gridX, int gridY);
};

#endif //LEDWALLSTUDIO_GRIDHEXAGON_H
