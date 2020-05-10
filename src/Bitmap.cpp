#include "Bitmap.h"

bool operator<(const QPoint &left, const QPoint &right)
{
    return left.x() < right.x() ? true : left.y() < right.y();
}

QByteArrayList Bitmap::toPixelStreamChunked(quint16 chunkSize) const
{
    QList<QByteArray> chunks;

    if (chunkSize < 7) {
        // a chunk carrying only one pixel requires 7 byte...
        return chunks;
    }
    if (empty()) {
        // we have no pixels...
        return chunks;
    }

    const int pixelsPerChunk = (chunkSize - 2) / 5;

    QMapIterator<QPoint, QColor> mi(*this);
    while (mi.hasNext()) {
        chunks.append(createChunk(mi, pixelsPerChunk));
    }

    return chunks;
}

QByteArray Bitmap::createChunk(QMapIterator<QPoint, QColor> &mi, int pixelsPerChunk) const
{
    QByteArray chunk;
    chunk.append((quint8)0x10);
    chunk.append((quint8)0x00);

    for (int pixelsInChunk = 0; pixelsInChunk < pixelsPerChunk; ++pixelsInChunk) {
        if (!mi.hasNext()) {
            break;
        }
        mi.next();

        chunk.append((quint8)mi.key().x());
        chunk.append((quint8)mi.key().y());
        chunk.append((quint8)mi.value().red());
        chunk.append((quint8)mi.value().green());
        chunk.append((quint8)mi.value().blue());
    }

    return chunk;
}
