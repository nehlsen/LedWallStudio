add_executable(LedWallStudio
        main.cpp
        BitmapEditor.cpp
        BitmapEditor/Grid.cpp
        BitmapEditor/GridRect.cpp
        BitmapEditor/GridHexagon.cpp
        Bitmap.cpp
        UdpConnector.cpp
        MainWindow.cpp
        SettingsDialog.cpp
        WallController/WallController.cpp
        WallController/Mode.cpp
        HttpConnector/HttpConnector.cpp
        HttpConnector/Config.cpp
        LedWallConfigWidget.cpp
        LedWallModes/ModeConfigWidget.cpp
        LedWallModes/ModesListModel.cpp
        Animations/BitmapFramesWidget.cpp
        Animations/FrameListModel.cpp
        Animations/Frame.cpp
        Animations/FrameListWriter.cpp
        Animations/FrameListReader.cpp
        )

target_link_libraries(LedWallStudio Qt5::Widgets Qt5::Network)
