#include "ModeOptions.h"
#include <LedMode/LedMode.h>
#include <LedMode/Wave.h>
#include <LedMode/MultiBars.h>
#include <LedMode/ModeText.h>

bool ModeOptions::writeToMode(const LedWallStudio::ModeOptions &options, LedWall::Mode::LedMode *mode)
{
    auto wave = dynamic_cast<LedWall::Mode::Wave*>(mode);
    if (wave) {
        return ModeOptions(options).write(wave);
    }

    auto multiBars = dynamic_cast<LedWall::Mode::MultiBars*>(mode);
    if (multiBars) {
        return ModeOptions(options).write(multiBars);
    }

    auto text = dynamic_cast<LedWall::Mode::ModeText*>(mode);
    if (text) {
        return ModeOptions(options).write(text);
    }

    return false;
}

LedWallStudio::ModeOptions ModeOptions::readFromMode(LedWall::Mode::LedMode *mode)
{
    auto wave = dynamic_cast<LedWall::Mode::Wave*>(mode);
    if (wave) {
        return ModeOptions::read(wave);
    }

    auto multiBars = dynamic_cast<LedWall::Mode::MultiBars*>(mode);
    if (multiBars) {
        return ModeOptions::read(multiBars);
    }

    auto text = dynamic_cast<LedWall::Mode::ModeText*>(mode);
    if (text) {
        return ModeOptions::read(text);
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

bool ModeOptions::write(LedWall::Mode::MultiBars *multiBars)
{
    if (m_options.contains("fadeRate")) {
        multiBars->setFadeRate(m_options.value("fadeRate").toInt());
    }
    if (m_options.contains("barTravelSpeed")) {
        multiBars->setBarTravelSpeed(m_options.value("barTravelSpeed").toInt());
    }
    if (m_options.contains("numberOfBars")) {
        multiBars->setNumberOfBars(m_options.value("numberOfBars").toInt());
    }
    if (m_options.contains("maximumFrameDelay")) {
        multiBars->setMaximumFrameDelay(m_options.value("maximumFrameDelay").toInt());
    }
    if (m_options.contains("barKeepsColor")) {
        multiBars->setBarKeepsColor(m_options.value("barKeepsColor").toBool());
    }
    if (m_options.contains("blendColor")) {
        multiBars->setBlendColor(m_options.value("blendColor").toBool());
    }

    return true;
}

LedWallStudio::ModeOptions ModeOptions::read(LedWall::Mode::MultiBars *multiBars)
{
    LedWallStudio::ModeOptions options;

    options.insert("fadeRate", multiBars->getFadeRate());
    options.insert("barTravelSpeed", multiBars->getBarTravelSpeed());
    options.insert("numberOfBars", multiBars->getNumberOfBars());
    options.insert("maximumFrameDelay", multiBars->getMaximumFrameDelay());
    options.insert("barKeepsColor", multiBars->isBarKeepsColor());
    options.insert("blendColor", multiBars->isBlendColor());

    return options;
}

bool ModeOptions::write(LedWall::Mode::ModeText *text)
{
    if (m_options.contains("text")) {
        text->setText(m_options.value("text").toString().toStdString());
    }
    if (m_options.contains("scrollSpeed")) {
        text->setScrollSpeed(m_options.value("scrollSpeed").toInt());
    }
    if (m_options.contains("scrollDirection")) {
        text->setScrollDirection(static_cast<LedWall::Mode::ModeText::ScrollDirection>(m_options.value("scrollDirection").toInt()));
    }

    return true;
}

LedWallStudio::ModeOptions ModeOptions::read(LedWall::Mode::ModeText *text)
{
    LedWallStudio::ModeOptions options;

    options.insert("text", QString::fromStdString(text->getText()));
    options.insert("scrollSpeed", text->getScrollSpeed());
    options.insert("scrollDirection", text->getScrollDirection());

    return options;
}
