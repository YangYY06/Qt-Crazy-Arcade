cmake_minimum_required(VERSION 3.5)

project(bombermanQT VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
#find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Multimedia REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        constants.h
        Game.cpp
        Game.h
        Player.cpp
        Player.h
        Map.cpp
        Map.h
        Flame.h
        Flame.cpp
        Bomb.cpp
        Bomb.h
        prop.H
        prop.cpp
        resourses.qrc
        MapCell.cpp
        MapCell.h
        DestructibleBlock.cpp
        DestructibleBlock.h
        IndestructibleBlock.cpp
        IndestructibleBlock.h
        #        Block.cpp
        #        Block.h
        EmptyBlock.cpp
        EmptyBlock.h
        Health.cpp
        Health.h
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        GameIsWin.cpp
        GameIsWin.h
        GameIsOver.cpp
        GameIsOver.h
        )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(bombermanQT
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET bombermanQT APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(bombermanQT SHARED
            ${PROJECT_SOURCES}
                MapCell.cpp MapCell.h)
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(bombermanQT
            ${PROJECT_SOURCES}
                MapCell.cpp MapCell.h)
    endif()
endif()

target_link_libraries(bombermanQT PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
#target_link_libraries(bombermanQT PRIVATE Qt${QT_VERSION_MAJOR}::Multimedia)

set_target_properties(bombermanQT PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(bombermanQT)
endif()
