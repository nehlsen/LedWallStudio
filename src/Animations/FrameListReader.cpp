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

        FrameList::iterator it;
        if (frames.isEmpty()) {
            // start first frame
            frames.append({QString::number(frameNumber++), (quint8)delay, Bitmap()});
        } else if ((quint8)delay > 0) {
            // copy previous frame and apply delta
            frames.append({QString::number(frameNumber++), (quint8)delay, Bitmap(frames.last().bitmap)});
        } // else, no delay: "continue" to write to previous bitmap

        it = frames.end() - 1;

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

            (*it).bitmap.insert({(quint8)x, (quint8)y}, QColor((quint8)r, (quint8)g, (quint8)b));
        }
        if ((*it).bitmap.size() != pixelsInFrame) {
            // hmmm....
            // FIXME read error?
        }
    }

    return frames;
}
