#ifndef LEDWALLSTUDIO_FRAME_H
#define LEDWALLSTUDIO_FRAME_H

#include <QtCore/QList>
#include "../Bitmap.h"

struct Frame {
    QString name;
    // TODO delay
    Bitmap bitmap;
};

typedef QList<Frame> FrameList;

#endif //LEDWALLSTUDIO_FRAME_H
