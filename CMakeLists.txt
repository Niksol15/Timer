cmake_minimum_required(VERSION 3.5)

project(Timer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Gui Qml Quick Multimedia QuickControls2 REQUIRED)

add_executable(Timer
  interface/main.cpp
  interface/timer.h
  interface/timer.cpp
  interface/logger.h
  interface/logger.cpp
  qml.qrc
)

target_link_libraries(Timer
           Qt5::Core
           Qt5::Gui
           Qt5::Qml
           Qt5::Quick
           Qt5::Multimedia
           Qt5::QuickControls2
           )
