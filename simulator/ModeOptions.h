#ifndef LEDWALLSTUDIO_MODEOPTIONS_H
#define LEDWALLSTUDIO_MODEOPTIONS_H

#include <WallController/Mode.h>

namespace LedWall {
namespace Mode{
class LedMode;
class Wave;
class MultiBars;
class Text;
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

    bool write(LedWall::Mode::MultiBars *multiBars);
    static LedWallStudio::ModeOptions read(LedWall::Mode::MultiBars *multiBars);

    bool write(LedWall::Mode::Text *text);
    static LedWallStudio::ModeOptions read(LedWall::Mode::Text *text);
};

#endif //LEDWALLSTUDIO_MODEOPTIONS_H
