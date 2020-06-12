add_executable(LedWallStudio
        LedWallConfigWidget.cpp
        main.cpp
        MainWindow.cpp
        SettingsDialog.cpp
        UdpConnector.cpp

        Animations/BitmapFramesWidget.cpp
        Animations/Frame.cpp
        Animations/FrameListModel.cpp
        Animations/FrameListReader.cpp
        Animations/FrameListWriter.cpp

        HttpConnector/Config.cpp
        HttpConnector/HttpConnector.cpp
        )

target_include_directories(LedWallStudio PRIVATE
        ../lib
        )

target_link_libraries(LedWallStudio LedWallStudioLib Qt5::Widgets Qt5::Network)
