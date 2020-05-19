cmake_minimum_required(VERSION 3.15)
project(LedWallStudio)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

add_subdirectory(src)
add_subdirectory(test)
