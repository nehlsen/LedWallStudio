#ifndef LEDWALLSTUDIO_CHSV_H
#define LEDWALLSTUDIO_CHSV_H

#include "CRGB.h"

class CHSV : public CRGB
{
public:
    CHSV(quint8 h, quint8 s, quint8 v);
};

#endif //LEDWALLSTUDIO_CHSV_H
