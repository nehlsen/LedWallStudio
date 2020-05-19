find_package(Qt5 COMPONENTS Test REQUIRED)

add_executable(BitmapTest BitmapTest.cpp ../src/Bitmap.cpp)
add_test(BitmapTest BitmapTest)
target_link_libraries(BitmapTest Qt5::Gui Qt5::Test)
