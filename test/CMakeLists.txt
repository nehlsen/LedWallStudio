find_package(Qt5 COMPONENTS Test REQUIRED)

add_executable(BitmapTest BitmapTest.cpp ../src/Bitmap.cpp)
add_test(BitmapTest BitmapTest)
target_link_libraries(BitmapTest Qt5::Gui Qt5::Test)

add_executable(FrameListWriterTest Animations/FrameListWriterTest.cpp ../src/Bitmap.cpp ../src/Animations/FrameListWriter.cpp)
add_test(FrameListWriterTest FrameListWriterTest)
target_link_libraries(FrameListWriterTest Qt5::Gui Qt5::Test)

add_executable(FrameListReaderTest Animations/FrameListReaderTest.cpp ../src/Bitmap.cpp ../src/Animations/FrameListReader.cpp)
add_test(FrameListReaderTest FrameListReaderTest)
target_link_libraries(FrameListReaderTest Qt5::Gui Qt5::Test)
