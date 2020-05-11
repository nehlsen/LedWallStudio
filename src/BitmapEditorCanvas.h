#ifndef LEDWALLSTUDIO_BITMAPEDITORCANVAS_H
#define LEDWALLSTUDIO_BITMAPEDITORCANVAS_H

#include <QtWidgets/QGraphicsScene>
#include "Bitmap.h"

class BitmapEditorCanvas : public QGraphicsScene
{
Q_OBJECT

public:
    explicit BitmapEditorCanvas(QObject *parent = nullptr);

    // set size in LEDs
    void setSize(quint32 width, quint32 height);

    const QColor &getPrimaryColor() const;
    void setPrimaryColor(const QColor &primaryColor);

    const QColor &getSecondaryColor() const;
    void setSecondaryColor(const QColor &secondaryColor);

    Bitmap getBitmap() const;
//    void setBitmap(const Bitmap& bitmap);

public slots:
    void clearCanvas();

signals:
    void bitmapChanged();
    void bitmapChanged(const QPoint &gridCoordinates);

protected:
    const qreal m_gridSize = 20;
    quint32 m_width = 1;
    quint32 m_height = 1;

    void drawGrid();

    QColor m_primaryColor = Qt::red;
    QColor m_secondaryColor = Qt::black;

    QPoint sceneToGridCoordinates(const QPointF sceneCoordinates) const;

    // TODO click and hold to colorize multiple pixels / draw...
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif //LEDWALLSTUDIO_BITMAPEDITORCANVAS_H
