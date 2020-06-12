#ifndef LEDWALLSTUDIO_GRID_H
#define LEDWALLSTUDIO_GRID_H

#include <QtCore/QSize>
#include <QtWidgets/QGraphicsScene>
#include <QtGui/QPen>
#include <QtGui/QBrush>

class Grid
{
public:
    explicit Grid(QGraphicsScene *scene);

    const QSize &getSize() const;
    void setSize(const QSize &size);

    const QPen &getLineColor() const;
    void setLineColor(const QPen &lineColor);

    const QBrush &getBackgroundColor() const;
    void setBackgroundColor(const QBrush &backgroundColor);

    virtual void drawGrid() = 0;

    virtual QPoint sceneToGridCoordinates(const QPointF &sceneCoordinates) const = 0;
    virtual QPointF gridToSceneCoordinates(const QPoint &gridCoordinates) const = 0;

protected:
    QGraphicsScene *m_scene;

    QSize m_size;

    QPen m_lineColor;
    QBrush m_backgroundColor;
};

#endif //LEDWALLSTUDIO_GRID_H
