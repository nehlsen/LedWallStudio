#include "Bitmap.h"

bool operator<(const QPoint &left, const QPoint &right)
{
    return left.x() < right.x() ? true : left.y() < right.y();
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

        if (pixelsInChunk == 255 || !mi.hasNext()) {
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

    Bitmap theDiff(other);
    for (int x = 0; x <= tr.x(); ++x) {
        for (int y = 0; y <= tr.y(); ++y) {
            QPoint p(x, y);
            if (contains(p) && !theDiff.contains(p)) {
                // if point is not-set in other, explicitly set to black
                theDiff[p] = Qt::black;
            } else if (contains(p) && theDiff.contains(p) && value(p) == theDiff.value(p)) {
                // if this and other are the same, remove from diff
                theDiff.remove(p);
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
