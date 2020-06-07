add_executable(Simulator
        main.cpp
        MainWindow.cpp
        Simulator.cpp
        FakeConnector.cpp
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
        ../src/WallController/WallController.cpp
        ../src/WallController/Mode.cpp

        ../../esp/LedWall/main/LedMode/LedMode.cpp
        ../../esp/LedWall/main/LedMode/utilities.c
        ../../esp/LedWall/main/LedMode/LedModeStatus.cpp
        ../../esp/LedWall/main/LedMode/Bars.cpp
        ../../esp/LedWall/main/LedMode/MultiBars.cpp
        ../../esp/LedWall/main/LedMode/Breathe.cpp
#        ../../esp/LedWall/main/LedMode/Fire.cpp # requires palettes
        ../../esp/LedWall/main/LedMode/Fireworks.cpp
        ../../esp/LedWall/main/LedMode/Text.cpp
        ../../esp/LedWall/main/LedMode/MatesDemo.cpp
        ../../esp/LedWall/components/Mates-for-LEDs/LedMatrix/LedMatrix.cpp
        ../../esp/LedWall/components/Mates-for-LEDs/LedMatrix/PixelLocator.cpp

        ../../esp/LedWall/components/Mates-for-LEDs/GfxPrimitives/GfxPrimitive.cpp
        ../../esp/LedWall/components/Mates-for-LEDs/GfxPrimitives/Pixel.cpp
        ../../esp/LedWall/components/Mates-for-LEDs/GfxPrimitives/PixelMap.cpp
        ../../esp/LedWall/components/Mates-for-LEDs/GfxPrimitives/Point.cpp
        ../../esp/LedWall/components/Mates-for-LEDs/GfxPrimitives/Text.cpp
        ../../esp/LedWall/components/Mates-for-LEDs/GfxPrimitives/Rect.cpp
        ../../esp/LedWall/components/Mates-for-LEDs/GfxPrimitives/Line.cpp
#        ../../esp/LedWall/components/Mates-for-LEDs/GfxPrimitives/Circle.cpp
        )

target_include_directories(Simulator PRIVATE
        support
        ../../esp/LedWall/components/Mates-for-LEDs/LedMatrix
        ../../esp/LedWall/components/Mates-for-LEDs/GfxPrimitives
        )
target_link_libraries(Simulator Qt5::Widgets)
