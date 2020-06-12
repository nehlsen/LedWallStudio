#ifndef LEDWALLSTUDIO_BITMAPEDITOR_H
#define LEDWALLSTUDIO_BITMAPEDITOR_H

#include <QtWidgets/QGraphicsView>
#include "../Bitmap.h"

class Grid;

class BitmapEditor : public QGraphicsView
{
Q_OBJECT

public:
    enum GridMode { GridModeRect, GridModeHexagon };
    explicit BitmapEditor(QWidget *parent = nullptr);
    explicit BitmapEditor(GridMode gridMode, QWidget *parent = nullptr);

    // set grid size / size in LEDs
    [[deprecated]]
    void setSize(quint32 width, quint32 height);
    [[deprecated("by getGridSize")]]
    QSize getSize() const { return getGridSize(); }
    [[deprecated("by setGridSize")]]
    void setSize(const QSize &size) { setGridSize(size); }

    QSize getGridSize() const;
    void setGridSize(const QSize &size);

    const QColor &getPrimaryColor() const;
    void setPrimaryColor(const QColor &primaryColor);

    const QColor &getSecondaryColor() const;
    void setSecondaryColor(const QColor &secondaryColor);

    Bitmap getBitmap() const;
    void setBitmap(const Bitmap& bitmap);

public slots:
    void clearCanvas();

signals:
    void bitmapChanged();
    void bitmapChanged(const QPoint &gridCoordinates);

protected:
    QGraphicsScene *m_scene;

    void drawGrid();
    Grid *m_grid = nullptr;

    QColor m_primaryColor = Qt::red;
    QColor m_secondaryColor = Qt::black;

    QPoint viewToGridCoordinates(const QPoint &viewCoordinates) const;
    QPoint gridToViewCoordinates(const QPoint &gridCoordinates) const;

    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    bool paintAction(QMouseEvent *event);
};

#endif //LEDWALLSTUDIO_BITMAPEDITOR_H
