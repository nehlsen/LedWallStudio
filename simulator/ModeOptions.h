#ifndef LEDWALLSTUDIO_MODEOPTIONS_H
#define LEDWALLSTUDIO_MODEOPTIONS_H

#include "../src/WallController/Mode.h"

namespace LedWall {
namespace Mode{
class LedMode;
class Wave;
}
}

class ModeOptions
{
public:
    static bool writeToMode(const LedWallStudio::ModeOptions &options, LedWall::Mode::LedMode *mode);
    static LedWallStudio::ModeOptions readFromMode(LedWall::Mode::LedMode *mode);

protected:
    ModeOptions(const LedWallStudio::ModeOptions &options);
    LedWallStudio::ModeOptions m_options;

    bool write(LedWall::Mode::Wave *wave);
    static LedWallStudio::ModeOptions read(LedWall::Mode::Wave *wave);
};

#endif //LEDWALLSTUDIO_MODEOPTIONS_H