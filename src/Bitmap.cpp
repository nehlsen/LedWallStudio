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

Bitmap Bitmap::diff(const Bitmap &other) const
{
    QPoint tr(topRight());
    if (other.topRight().x() > tr.x()) tr.setX(other.topRight().x());
    if (other.topRight().y() > tr.y()) tr.setY(other.topRight().y());

    Bitmap theDiff(other);
    for (int x = 0; x < tr.x(); ++x) {
        for (int y = 0; y < tr.y(); ++y) {
            QPoint p(x, y);
            // if this and other are the same, remove from diff
            if (contains(p) && theDiff.contains(p) && value(p) == theDiff.value(p)) {
                theDiff.remove(p);
            }
            // if point is not-set in other, explicitly set to black
            if (contains(p) && !theDiff.contains(p)) {
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
