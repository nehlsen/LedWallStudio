#include "Bitmap.h"
#include <QtCore/QDebug>

bool operator<(const QPoint &left, const QPoint &right)
{
    if (left.x() == right.x()) {
        return left.y() < right.y();
    }

    return left.x() < right.x();
}

QByteArray Bitmap::toPixelStream() const
{
    const QByteArrayList &chunkedStream = toPixelStreamChunked(count() * 5 + 2);
    if (chunkedStream.length() != 1) {
        return QByteArray();
    }

    return chunkedStream.first();
}

QByteArrayList Bitmap::toPixelStreamChunked(quint16 chunkSize) const
{
    QByteArrayList chunks;

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

QByteArray Bitmap::toPixelStream1a(quint8 delay) const
{
    const int maxChunkSize = 255;

    QByteArray pixelStream;

    if (empty()) {
        pixelStream.append(delay); // delay
        pixelStream.append((quint8)0); // number of pixels

        return pixelStream;
    }

    QMapIterator<QPoint, QColor> mi(*this);
    bool isFirstChunk = true;
    QByteArray currentChunk;
    quint8 pixelsInChunk = 0;
    do {
        mi.next();

        currentChunk.append((quint8)mi.key().x());
        currentChunk.append((quint8)mi.key().y());
        currentChunk.append((quint8)mi.value().red());
        currentChunk.append((quint8)mi.value().green());
        currentChunk.append((quint8)mi.value().blue());
        ++pixelsInChunk;

        if (pixelsInChunk == maxChunkSize || !mi.hasNext()) {
            pixelStream.append(isFirstChunk ? delay : (quint8)0x00); // delay
            pixelStream.append(pixelsInChunk); // number of pixels
            pixelStream.append(currentChunk);

            isFirstChunk = false;
            currentChunk.clear();
            pixelsInChunk = 0;
        }
    } while (mi.hasNext());

    return pixelStream;
}

Bitmap Bitmap::diff(const Bitmap &other) const
{
    QPoint tr(topRight());
    if (other.topRight().x() > tr.x()) tr.setX(other.topRight().x());
    if (other.topRight().y() > tr.y()) tr.setY(other.topRight().y());

    Bitmap theDiff;
    for (int x = 0; x <= tr.x(); ++x) {
        for (int y = 0; y <= tr.y(); ++y) {
            QPoint p(x, y);
            if (value(p).isValid() && other.value(p).isValid() && value(p) != other.value(p)) {
                // pixel has changed
                theDiff[p] = other.value(p);
            } else if (!value(p).isValid() && other.value(p).isValid()) {
                // pixel was added
                theDiff[p] = other.value(p);
            } else if (value(p).isValid() && !other.value(p).isValid()) {
                // pixel was removed
                theDiff[p] = Qt::black;
            }
        }
    }

    return theDiff;
}

QPoint Bitmap::topRight() const
{
    QPoint tr;
    for (QPoint p : keys()) {
        if (p.x() > tr.x()) tr.setX(p.x());
        if (p.y() > tr.y()) tr.setY(p.y());
    }

    return tr;
}

QDebug operator<<(QDebug dbg, const Bitmap &bitmap)
{
    QDebugStateSaver saver(dbg);

    for (int y = bitmap.topRight().y(); y >= 0; --y) {
        for (int x = 0; x <= bitmap.topRight().x(); ++x) {
            const QColor &c = bitmap[{x,y}];
            dbg.nospace().noquote()
                << QString("[%1/%2 %3,%4,%5] ")
                    .arg(x, 2, 10, QChar(' '))
                    .arg(y, 2, 10, QChar(' '))
                    .arg(c.red(), 3, 10, QChar(' '))
                    .arg(c.green(), 3, 10, QChar(' '))
                    .arg(c.blue(), 3, 10, QChar(' '))
            ;
        }

        dbg.nospace() << "\n ";
    }

    return dbg;
}
