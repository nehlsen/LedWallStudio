
add_executable(LedWallStudio
        main.cpp
        BitmapEditorCanvas.cpp
        Bitmap.cpp
        UdpConnector.cpp
        MainWindow.cpp
        SettingsDialog.cpp
        HttpConnector/HttpConnector.cpp
        HttpConnector/Config.cpp
        )

target_link_libraries(LedWallStudio Qt5::Widgets Qt5::Network)
