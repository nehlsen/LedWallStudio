#ifndef LEDWALLSTUDIO_FRAMELISTWRITER_H
#define LEDWALLSTUDIO_FRAMELISTWRITER_H

#include "Frame.h"

class FrameListWriter
{
public:
    static QByteArray toByteArray(const FrameList &frames);
};

#endif //LEDWALLSTUDIO_FRAMELISTWRITER_H
