#include "ModeOptions.h"
#include <LedMode/LedMode.h>
#include <LedMode/Wave.h>

bool ModeOptions::writeToMode(const LedWallStudio::ModeOptions &options, LedWall::Mode::LedMode *mode)
{
    auto wave = dynamic_cast<LedWall::Mode::Wave*>(mode);
    if (wave) {
        return ModeOptions(options).write(wave);
    }

    return false;
}

LedWallStudio::ModeOptions ModeOptions::readFromMode(LedWall::Mode::LedMode *mode)
{
    auto wave = dynamic_cast<LedWall::Mode::Wave*>(mode);
    if (wave) {
        return ModeOptions::read(wave);
    }

    return LedWallStudio::ModeOptions();
}

ModeOptions::ModeOptions(const LedWallStudio::ModeOptions &options):
    m_options(options)
{}

bool ModeOptions::write(LedWall::Mode::Wave *wave)
{
    if (m_options.contains("waveMode")) {
        wave->setWaveMode(static_cast<LedWall::Mode::Wave::WaveMode>(m_options.value("waveMode").toInt()));
    }
    if (m_options.contains("waveDirection")) {
        wave->setWaveDirection(static_cast<LedWall::Mode::Wave::WaveDirection>(m_options.value("waveDirection").toInt()));
    }
    if (m_options.contains("waveLength")) {
        wave->setWaveLength(m_options.value("waveLength").toInt());
    }
    if (m_options.contains("speed")) {
        wave->setSpeed(m_options.value("speed").toInt());
    }

    if (m_options.contains("colorHueLow")) {
        wave->setModHue(m_options.value("colorHueLow").toInt(), wave->getModHue().second);
    }
    if (m_options.contains("colorHueHigh")) {
        wave->setModHue(wave->getModHue().first, m_options.value("colorHueHigh").toInt());
    }
    if (m_options.contains("colorSaturationLow")) {
        wave->setModSaturation(m_options.value("colorSaturationLow").toInt(), wave->getModSaturation().second);
    }
    if (m_options.contains("colorSaturationHigh")) {
        wave->setModSaturation(wave->getModSaturation().first, m_options.value("colorSaturationHigh").toInt());
    }
    if (m_options.contains("colorValueLow")) {
        wave->setModValue(m_options.value("colorValueLow").toInt(), wave->getModValue().second);
    }
    if (m_options.contains("colorValueHigh")) {
        wave->setModValue(wave->getModValue().first, m_options.value("colorValueHigh").toInt());
    }

    return true;
}

LedWallStudio::ModeOptions ModeOptions::read(LedWall::Mode::Wave *wave)
{
    LedWallStudio::ModeOptions options;

    options.insert("waveMode", wave->getWaveMode());
    options.insert("waveDirection", wave->getWaveDirection());
    options.insert("waveLength", wave->getWaveLength());
    options.insert("speed", wave->getSpeed());

    options.insert("colorHueLow", wave->getModHue().first);
    options.insert("colorHueHigh", wave->getModHue().second);
    options.insert("colorSaturationLow", wave->getModSaturation().first);
    options.insert("colorSaturationHigh", wave->getModSaturation().second);
    options.insert("colorValueLow", wave->getModValue().first);
    options.insert("colorValueHigh", wave->getModValue().second);

    return options;
}
