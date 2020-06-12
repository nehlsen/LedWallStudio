#include "FrameListWriter.h"

QByteArray FrameListWriter::toByteArray(const FrameList &frames)
{
    QByteArray data;
    data.append((quint8)0x1a); // protocol
    data.append((quint8)0x00); // options

    QListIterator<Frame> it(frames);
    while (it.hasNext()) {
        if (!it.hasPrevious()) {
            const Frame &frame = it.next();
            data.append(frame.bitmap.toPixelStream1a(frame.delay));
        } else {
            const Frame &previousFrame = it.peekPrevious();
            const Frame &frame = it.next();
            data.append(previousFrame.bitmap.diff(frame.bitmap).toPixelStream1a(frame.delay));
        }
    }

    return data;
}
