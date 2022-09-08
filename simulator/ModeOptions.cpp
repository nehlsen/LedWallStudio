#include "ModeOptions.h"
#include <LedMode/LedMode.h>
#include <LedMode/Wave.h>
#include <LedMode/MultiBars.h>
#include <LedMode/ModeText.h>
#include <LedMode/ModeTime.h>
#include <LedMode/GameOfLife.h>
#include <LedMode/Bubbles.h>

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

    auto time = dynamic_cast<LedWall::Mode::ModeTime*>(mode);
    if (time) {
        return ModeOptions(options).write(time);
    }

    auto text = dynamic_cast<LedWall::Mode::ModeText*>(mode);
    if (text) {
        return ModeOptions(options).write(text);
    }

    auto gameOfLife = dynamic_cast<LedWall::Mode::GameOfLife*>(mode);
    if (gameOfLife) {
        return ModeOptions(options).write(gameOfLife);
    }

    auto bubbles = dynamic_cast<LedWall::Mode::Bubbles*>(mode);
    if (bubbles) {
        return ModeOptions(options).write(bubbles);
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

    auto time = dynamic_cast<LedWall::Mode::ModeTime*>(mode);
    if (time) {
        return ModeOptions::read(time);
    }

    auto text = dynamic_cast<LedWall::Mode::ModeText*>(mode);
    if (text) {
        return ModeOptions::read(text);
    }

    auto gameOfLife = dynamic_cast<LedWall::Mode::GameOfLife*>(mode);
    if (gameOfLife) {
        return ModeOptions::read(gameOfLife);
    }

    auto bubbles = dynamic_cast<LedWall::Mode::Bubbles*>(mode);
    if (bubbles) {
        return ModeOptions::read(bubbles);
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

    return true;
}

LedWallStudio::ModeOptions ModeOptions::read(LedWall::Mode::MultiBars *multiBars)
{
    LedWallStudio::ModeOptions options;

    options.insert("fadeRate", multiBars->getFadeRate());
    options.insert("barTravelSpeed", multiBars->getBarTravelSpeed());
    options.insert("numberOfBars", multiBars->getNumberOfBars());
    options.insert("maximumFrameDelay", multiBars->getMaximumFrameDelay());

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
    if (m_options.contains("scrollMode")) {
        text->setScrollMode(static_cast<LedWall::Mode::ModeText::ScrollMode>(m_options.value("scrollMode").toInt()));
    }

    return true;
}

LedWallStudio::ModeOptions ModeOptions::read(LedWall::Mode::ModeText *text)
{
    LedWallStudio::ModeOptions options;

    options.insert("text", QString::fromStdString(text->getText()));
    options.insert("scrollSpeed", text->getScrollSpeed());
    options.insert("scrollDirection", text->getScrollDirection());
    options.insert("scrollMode", text->getScrollMode());

    return options;
}

bool ModeOptions::write(LedWall::Mode::ModeTime *time)
{
    write(dynamic_cast<LedWall::Mode::ModeText*>(time));

    if (m_options.contains("variant")) {
        time->setVariant(static_cast<LedWall::Mode::ModeTime::Variant>(m_options.value("variant").toInt()));
    }
    if (m_options.contains("parameter")) {
        time->setVariantParameter(m_options.value("parameter").toInt());
    }

    return true;
}

LedWallStudio::ModeOptions ModeOptions::read(LedWall::Mode::ModeTime *time)
{
    LedWallStudio::ModeOptions options = read(dynamic_cast<LedWall::Mode::ModeText*>(time));

    options.insert("variant", time->getVariant());
    options.insert("parameter", time->getVariantParameter());

    return options;
}

bool ModeOptions::write(LedWall::Mode::GameOfLife *gameOfLife)
{
    if (m_options.contains("generationDelay")) {
        gameOfLife->setGenerationDelay(m_options.value("generationDelay").toInt());
    }

    return true;
}

LedWallStudio::ModeOptions ModeOptions::read(LedWall::Mode::GameOfLife *gameOfLife)
{
    LedWallStudio::ModeOptions options;

    options.insert("generationDelay", gameOfLife->getGenerationDelay());

    return options;
}

bool ModeOptions::write(LedWall::Mode::Bubbles *bubbles)
{
    if (m_options.contains("numberOfBubbles")) {
        bubbles->setNumberOfBubbles(m_options.value("numberOfBubbles").toInt());
    }
    if (m_options.contains("maximumBubbleSize")) {
        bubbles->setMaximumBubbleSize(m_options.value("maximumBubbleSize").toInt());
    }
    if (m_options.contains("speed")) {
        bubbles->setSpeed(m_options.value("speed").toInt());
    }
    if (m_options.contains("maximumFrameDelay")) {
        bubbles->setMaximumFrameDelay(m_options.value("maximumFrameDelay").toInt());
    }

    return true;
}

LedWallStudio::ModeOptions ModeOptions::read(LedWall::Mode::Bubbles *bubbles)
{
    LedWallStudio::ModeOptions options;

    options.insert("numberOfBubbles", bubbles->getNumberOfBubbles());
    options.insert("maximumBubbleSize", bubbles->getMaximumBubbleSize());
    options.insert("speed", bubbles->getSpeed());
    options.insert("maximumFrameDelay", bubbles->getMaximumFrameDelay());

    return options;
}
