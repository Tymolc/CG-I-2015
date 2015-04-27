cmake_minimum_required(VERSION 2.6)

project(FrameworkQt)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(target FrameworkQt)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

set(sources
     src/main.cpp
     src/mainwindow.h
     src/mainwindow.cpp
     src/imageview.h
     src/imageview.cpp
     src/example.h
     src/example.cpp
)

add_executable(${target} ${sources})

qt5_use_modules(${target} Core Gui Widgets)
