#ifndef LEDWALLSTUDIO_BITMAP_H
#define LEDWALLSTUDIO_BITMAP_H

#include <QtCore/QMap>
#include <QtCore/QPoint>
#include <QtGui/QColor>

bool operator<(const QPoint &left, const QPoint &right);

class Bitmap : public QMap<QPoint, QColor>
{
    // TODO size(QSize)
};

#endif //LEDWALLSTUDIO_BITMAP_H
