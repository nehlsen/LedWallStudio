#include <QtCore/QBuffer>
#include "FrameListReader.h"

FrameList FrameListReader::fromByteArray(QByteArray &data)
{
    QBuffer buffer(&data);
    buffer.open(QIODevice::ReadOnly);
    return fromIoDevice(buffer);
}

FrameList FrameListReader::fromIoDevice(QIODevice &ioDevice)
{
    FrameList frames;

    if (ioDevice.bytesAvailable() < 9) {
        // 2byte header + 2byte frame header + 5byte for one pixel -> less than that? don't even bother!
        return frames;
    }

    char buffer;
    if (ioDevice.read(&buffer, 1) != 1 || buffer != 0x1a) return frames; // protocol
    if (ioDevice.read(&buffer, 1) != 1 || buffer != 0x00) return frames; // options

    int frameNumber = 0;
    while (ioDevice.bytesAvailable() >= 7) {
        char delay, pixelsInFrame;
        if (ioDevice.read(&delay, 1) != 1) break;
        if (ioDevice.read(&pixelsInFrame, 1) != 1) break;

        // TODO delay of zero should merge to bitmaps into one
        //  to e.g. handle bitmaps with more than 256 pixels

        // FIXME the data stream stores delta frames!
        //  this has to be reversed

        Bitmap bitmap;
        for (int i = 0; i < pixelsInFrame; ++i) {
            if (ioDevice.bytesAvailable() < 5) {
                break;
            }

            char x, y, r, g, b;
            ioDevice.read(&x, 1);
            ioDevice.read(&y, 1);
            ioDevice.read(&r, 1);
            ioDevice.read(&g, 1);
            ioDevice.read(&b, 1);

            bitmap.insert({(quint8)x, (quint8)y}, QColor((quint8)r, (quint8)g, (quint8)b));
        }
        if (bitmap.size() != pixelsInFrame) {
            // hmmm....
            // FIXME read error?
        }

        frames.append({QString::number(frameNumber++), bitmap});
    }

    return frames;
}
