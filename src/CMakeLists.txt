add_executable(LedWallStudio
        main.cpp
        BitmapEditor.cpp
        Bitmap.cpp
        UdpConnector.cpp
        MainWindow.cpp
        SettingsDialog.cpp
        HttpConnector/HttpConnector.cpp
        HttpConnector/Config.cpp
        LedWallConfigWidget.cpp
        HttpConnector/Mode.cpp
        LedWallModes/ModeConfigWidget.cpp
        LedWallModes/ModesListModel.cpp
        Animations/BitmapFramesWidget.cpp
        Animations/FrameListModel.cpp
        Animations/Frame.cpp
        Animations/FrameListWriter.cpp
        Animations/FrameListReader.cpp
        )

target_link_libraries(LedWallStudio Qt5::Widgets Qt5::Network)
