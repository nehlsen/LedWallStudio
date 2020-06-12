#ifndef LEDWALLSTUDIO_FRAME_H
#define LEDWALLSTUDIO_FRAME_H

#include <QtCore/QList>
#include <Bitmap.h>

struct Frame {
    QString name;
    quint8 delay; // delay BEFORE this frame
    Bitmap bitmap;
};

typedef QList<Frame> FrameList;

#endif //LEDWALLSTUDIO_FRAME_H
