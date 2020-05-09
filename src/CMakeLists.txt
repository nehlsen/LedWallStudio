
add_executable(LedWallStudio
        main.cpp
        BitmapEditorWidget.cpp
        BitmapEditorCanvas.cpp
        Bitmap.cpp
        UdpConnector.cpp
        )

target_link_libraries(LedWallStudio Qt5::Widgets Qt5::Network)
