set(LEDWALL_SRC_DIR ../../LedWall)

add_executable(Simulator
        main.cpp
        MainWindow.cpp
        Simulator.cpp
        FakeConnector.cpp
        ModeOptions.cpp
        PlaybackControlWidget.cpp

        support/esp32-hal.cpp
        support/FastLED.cpp
        support/cJSON.cpp

        ../src/Bitmap.cpp
        ../src/BitmapEditor.cpp
        ../src/BitmapEditor/Grid.cpp
        ../src/BitmapEditor/GridRect.cpp
        ../src/BitmapEditor/GridHexagon.cpp
        ../src/LedWallModes/ModeConfigWidget.cpp
        ../src/LedWallModes/ModesListModel.cpp
        ../src/LedWallModes/ModeOptionsWidget.cpp
        ../src/LedWallModes/WaveOptionsWidget.cpp
        ../src/LedWallModes/MultiBarsOptionsWidget.cpp
        ../src/WallController/WallController.cpp
        ../src/WallController/Mode.cpp

        ${LEDWALL_SRC_DIR}/main/LedMode/LedMode.cpp
        ${LEDWALL_SRC_DIR}/main/LedMode/utilities.c
        ${LEDWALL_SRC_DIR}/main/LedMode/LedModeStatus.cpp
        ${LEDWALL_SRC_DIR}/main/LedMode/Bars.cpp
        ${LEDWALL_SRC_DIR}/main/LedMode/MultiBars.cpp
#        ${LEDWALL_SRC_DIR}/main/LedMode/Breathe.cpp
#        ${LEDWALL_SRC_DIR}/main/LedMode/Fire.cpp # requires palettes
        ${LEDWALL_SRC_DIR}/main/LedMode/Fireworks.cpp
        ${LEDWALL_SRC_DIR}/main/LedMode/Text.cpp
        ${LEDWALL_SRC_DIR}/main/LedMode/MatesDemo.cpp
        ${LEDWALL_SRC_DIR}/main/LedMode/Wave.cpp
        ${LEDWALL_SRC_DIR}/components/Mates-for-LEDs/LedMatrix/LedMatrix.cpp
        ${LEDWALL_SRC_DIR}/components/Mates-for-LEDs/LedMatrix/PixelLocator.cpp

        ${LEDWALL_SRC_DIR}/components/Mates-for-LEDs/GfxPrimitives/GfxPrimitive.cpp
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
        ${LEDWALL_SRC_DIR}/main
        ${LEDWALL_SRC_DIR}/components/Mates-for-LEDs/LedMatrix
        ${LEDWALL_SRC_DIR}/components/Mates-for-LEDs/GfxPrimitives
        )
target_link_libraries(Simulator Qt5::Widgets)
