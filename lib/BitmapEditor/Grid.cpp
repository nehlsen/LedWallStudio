#include "Grid.h"

Grid::Grid(QGraphicsScene *scene):
    m_scene(scene)
{
    setLineColor(QPen(Qt::white));
    setBackgroundColor(QBrush(Qt::black));
}

const QSize &Grid::getSize() const
{
    return m_size;
}

void Grid::setSize(const QSize &size)
{
    m_size = size;
}

const QPen &Grid::getLineColor() const
{
    return m_lineColor;
}

void Grid::setLineColor(const QPen &lineColor)
{
    m_lineColor = lineColor;
}

const QBrush &Grid::getBackgroundColor() const
{
    return m_backgroundColor;
}

void Grid::setBackgroundColor(const QBrush &backgroundColor)
{
    m_backgroundColor = backgroundColor;
}
