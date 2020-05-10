
add_executable(LedWallStudio
        main.cpp
        BitmapEditorCanvas.cpp
        Bitmap.cpp
        UdpConnector.cpp
        MainWindow.cpp
        )

target_link_libraries(LedWallStudio Qt5::Widgets Qt5::Network)
