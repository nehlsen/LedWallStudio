set(LEDWALL_SRC_DIR ../../LedWall)

add_executable(Simulator
        main.cpp
        MainWindow.cpp
        Simulator.cpp
        FakeConnector.cpp
        ModeOptions.cpp
        PlaybackControlWidget.cpp

        support/esp32-hal.cpp
        support/esp_log.cpp
        support/FastLED.cpp
        support/cJSON.cpp
        support/CRGBPalette16.cpp
        support/CRGB.cpp
        support/CHSV.cpp
        support/fill_x.cpp

        ${LEDWALL_SRC_DIR}/main/LedMode/LedMode.cpp
        ${LEDWALL_SRC_DIR}/main/LedMode/utilities.c
        ${LEDWALL_SRC_DIR}/main/LedMode/LedModeStatus.cpp
        ${LEDWALL_SRC_DIR}/main/LedMode/Bars.cpp
        ${LEDWALL_SRC_DIR}/main/LedMode/MultiBars.cpp
#        ${LEDWALL_SRC_DIR}/main/LedMode/Breathe.cpp
#        ${LEDWALL_SRC_DIR}/main/LedMode/Fire.cpp # requires palettes
        ${LEDWALL_SRC_DIR}/main/LedMode/Fireworks.cpp
        ${LEDWALL_SRC_DIR}/main/LedMode/ModeTime.cpp
        ${LEDWALL_SRC_DIR}/main/LedMode/ModeText.cpp
        ${LEDWALL_SRC_DIR}/main/LedMode/MatesDemo.cpp
        ${LEDWALL_SRC_DIR}/main/LedMode/Wave.cpp
        ${LEDWALL_SRC_DIR}/main/LedMode/FancyDemo.cpp
        ${LEDWALL_SRC_DIR}/main/LedMode/FancyDemo/FancyDemoPart.cpp
        ${LEDWALL_SRC_DIR}/main/LedMode/FancyDemo/FdBarsGrow.cpp
        ${LEDWALL_SRC_DIR}/main/LedMode/FancyDemo/FdBarsOpen.cpp
        ${LEDWALL_SRC_DIR}/main/LedMode/FancyDemo/FancyDemoPart3.cpp
        ${LEDWALL_SRC_DIR}/main/LedMode/FancyDemo/FancyDemoPart4.cpp
        ${LEDWALL_SRC_DIR}/main/LedMode/FancyDemo/FdCubeRoll.cpp
        ${LEDWALL_SRC_DIR}/main/LedMode/FancyDemo/FdCubeGrow.cpp
        ${LEDWALL_SRC_DIR}/main/LedMode/FancyDemo/FdColorRays.cpp
        ${LEDWALL_SRC_DIR}/main/LedMode/FancyDemo/FdSprinkle.cpp
        ${LEDWALL_SRC_DIR}/main/LedMode/FancyDemo/FdExplodingLetters.cpp
        ${LEDWALL_SRC_DIR}/main/LedMode/FancyDemo/FdCircleGrow.cpp
        ${LEDWALL_SRC_DIR}/main/LedMode/GameOfLife.cpp
#        ${LEDWALL_SRC_DIR}/main/LedMode/GameOfLife/GameOfLife.cpp
#        ${LEDWALL_SRC_DIR}/main/LedMode/GameOfLife/World.cpp

        ${LEDWALL_SRC_DIR}/components/Mates-for-LEDs/LedMatrix/LedMatrix.cpp
        ${LEDWALL_SRC_DIR}/components/Mates-for-LEDs/LedMatrix/PixelLocator.cpp
        ${LEDWALL_SRC_DIR}/components/Mates-for-LEDs/LedMatrix/color_utils.cpp

        ${LEDWALL_SRC_DIR}/components/Mates-for-LEDs/GfxPrimitives/GfxPrimitive.cpp
        ${LEDWALL_SRC_DIR}/components/Mates-for-LEDs/GfxPrimitives/GfxCanvas.cpp
        ${LEDWALL_SRC_DIR}/components/Mates-for-LEDs/GfxPrimitives/Canvas.cpp
        ${LEDWALL_SRC_DIR}/components/Mates-for-LEDs/GfxPrimitives/Renderable.cpp
        ${LEDWALL_SRC_DIR}/components/Mates-for-LEDs/GfxPrimitives/Pixel.cpp
        ${LEDWALL_SRC_DIR}/components/Mates-for-LEDs/GfxPrimitives/PixelMap.cpp
        ${LEDWALL_SRC_DIR}/components/Mates-for-LEDs/GfxPrimitives/Point.cpp
        ${LEDWALL_SRC_DIR}/components/Mates-for-LEDs/GfxPrimitives/Text.cpp
        ${LEDWALL_SRC_DIR}/components/Mates-for-LEDs/GfxPrimitives/Rect.cpp
        ${LEDWALL_SRC_DIR}/components/Mates-for-LEDs/GfxPrimitives/Line.cpp
        ${LEDWALL_SRC_DIR}/components/Mates-for-LEDs/GfxPrimitives/Circle.cpp
        )

target_include_directories(Simulator PRIVATE
        support
        ../lib
        ${LEDWALL_SRC_DIR}/main
        ${LEDWALL_SRC_DIR}/components/Mates-for-LEDs/LedMatrix
        ${LEDWALL_SRC_DIR}/components/Mates-for-LEDs/GfxPrimitives
        )
target_link_libraries(Simulator LedWallStudioLib Qt5::Widgets)
