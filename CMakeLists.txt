cmake_minimum_required(VERSION 3.15)
project(LedWallStudio)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

add_subdirectory(lib)
add_subdirectory(studio)
add_subdirectory(simulator)
add_subdirectory(test)
