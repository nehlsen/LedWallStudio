
add_executable(LedWallStudio
        main.cpp
        BitmapEditorWidget.cpp
        BitmapEditorCanvas.cpp
        Bitmap.cpp Bitmap.h)

target_link_libraries(LedWallStudio Qt5::Widgets)
