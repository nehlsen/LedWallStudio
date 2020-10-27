set(LedWallStudioLib_src
        Bitmap.cpp
        BitmapEditor/BitmapEditor.cpp
        BitmapEditor/Grid.cpp
        BitmapEditor/GridRect.cpp
        BitmapEditor/GridHexagon.cpp
        LedWallModes/ModeConfigWidget.cpp
        LedWallModes/ModeOptionsWidget.cpp
        LedWallModes/ModesListModel.cpp
        LedWallModes/MultiBarsOptionsWidget.cpp
        LedWallModes/TextOptionsWidget.cpp
        LedWallModes/TimeOptionsWidget.cpp
        LedWallModes/WaveOptionsWidget.cpp
        LedWallModes/GameOfLifeOptionsWidget.cpp
        WallController/Mode.cpp
        WallController/WallController.cpp
        )
set(LedWallStudioLibDir ${CMAKE_CURRENT_SOURCE_DIR})
add_library(LedWallStudioLib ${LedWallStudioLib_src})
target_link_libraries(LedWallStudioLib Qt5::Widgets)
