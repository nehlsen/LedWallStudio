find_package(Qt5 COMPONENTS Test REQUIRED)

# move to `lib/test`
add_executable(BitmapTest BitmapTest.cpp ../lib/Bitmap.cpp)
add_test(BitmapTest BitmapTest)
target_include_directories(BitmapTest PRIVATE ../lib)
target_link_libraries(BitmapTest Qt5::Gui Qt5::Test)

# move to `studio/test`
add_executable(FrameListWriterTest Animations/FrameListWriterTest.cpp ../lib/Bitmap.cpp ../studio/Animations/FrameListWriter.cpp)
add_test(FrameListWriterTest FrameListWriterTest)
target_include_directories(FrameListWriterTest PRIVATE ../lib)
target_link_libraries(FrameListWriterTest Qt5::Gui Qt5::Test)

# move to `studio/test`
add_executable(FrameListReaderTest Animations/FrameListReaderTest.cpp ../lib/Bitmap.cpp ../studio/Animations/FrameListReader.cpp)
add_test(FrameListReaderTest FrameListReaderTest)
target_include_directories(FrameListReaderTest PRIVATE ../lib)
target_link_libraries(FrameListReaderTest Qt5::Gui Qt5::Test)
