#include "FrameListWriter.h"

QByteArray FrameListWriter::toByteArray(const FrameList &frames)
{
    QByteArray data;
    data.append((quint8)0x1a); // protocol
    data.append((quint8)0x00); // options

    QListIterator<Frame> it(frames);
    while (it.hasNext()) {
        if (!it.hasPrevious()) {
//            qDebug("FULL frame");
            data.append(it.next().bitmap.toPixelStream1a(/*TODO delay*/0));
        } else {
//            qDebug("DIFF frame");
            data.append(it.peekPrevious().bitmap.diff(it.next().bitmap).toPixelStream1a(/*TODO delay*/0));
        }
    }

    return data;
}
