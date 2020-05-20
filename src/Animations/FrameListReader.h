#ifndef LEDWALLSTUDIO_FRAMELISTREADER_H
#define LEDWALLSTUDIO_FRAMELISTREADER_H

#include <QtCore/QIODevice>
#include "Frame.h"

class FrameListReader
{
public:
    static FrameList fromByteArray(QByteArray &data);
    static FrameList fromIoDevice(QIODevice &ioDevice);
};

#endif //LEDWALLSTUDIO_FRAMELISTREADER_H
