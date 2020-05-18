#ifndef LEDWALLSTUDIO_BITMAP_H
#define LEDWALLSTUDIO_BITMAP_H

#include <QtCore/QMap>
#include <QtCore/QPoint>
//#include <QtCore/QMetaType>
#include <QtGui/QColor>

bool operator<(const QPoint &left, const QPoint &right);

class Bitmap : public QMap<QPoint, QColor>
{
public:
    // detect protocol itself
    static Bitmap fromRawData(const QByteArray &data);
    // protocol 0x10
    static Bitmap fromPixelStream(const QByteArray &data);
    // protocol 0x11
    static Bitmap fromQuadTree(const QByteArray &data);

    // convert bitmap to pixel stream - protocol 0x10
    QByteArray toPixelStream() const;
    QByteArrayList toPixelStreamChunked(quint16 chunkSize) const;

    QByteArray toQuadTree() const;
    QByteArray toQuadTreeChunked(quint16 chunkSize) const;

    QPoint topRight() const;

    // get a bitmap having only those pixels set to get from _this_ Bitmap to _other_ Bitmap
    Bitmap diff(const Bitmap &other) const;

protected:
    QByteArray createChunk(QMapIterator<QPoint, QColor> &mi, int pixelsPerChunk) const;
};

//Q_DECLARE_METATYPE(Bitmap)

#endif //LEDWALLSTUDIO_BITMAP_H
