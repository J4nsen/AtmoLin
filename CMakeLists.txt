cmake_minimum_required(VERSION 3.5)

project(AtmoLin VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets SerialPort)

add_subdirectory(Qt-Color-Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(AtmoLin
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        settingsdialog.cpp mainwindow.cpp atmolight.cpp ledarea.cpp main.cpp
        modes/flaschendrehen.cpp
        modes/individualfixedcolor.cpp
        modes/abstractmode.cpp modes/flaschendrehen.cpp modes/individualfixedcolor.cpp modes/onefixedcolor.cpp  modes/worm.cpp
        atmolight.h ledarea.h mainwindow.h settingsdialog.h
        modes/abstractmode.h modes/flaschendrehen.h modes/individualfixedcolor.h modes/onefixedcolor.h  modes/worm.h
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET AtmoLin APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(AtmoLin SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(AtmoLin
            ${PROJECT_SOURCES}
            atmolight.cpp atmolight.h ledarea.cpp ledarea.h main.cpp mainwindow.cpp mainwindow.h mainwindow.ui  settingsdialog.cpp settingsdialog.h settingsdialog.ui
            modes/abstractmode.cpp modes/abstractmode.h modes/flaschendrehen.cpp modes/flaschendrehen.h modes/individualfixedcolor.cpp modes/individualfixedcolor.h modes/onefixedcolor.cpp modes/onefixedcolor.h   modes/worm.cpp modes/worm.h
        )
    endif()
endif()

target_link_libraries(AtmoLin PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::SerialPort QtColorWidgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.AtmoLin)
endif()
set_target_properties(AtmoLin PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS AtmoLin
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(AtmoLin)
endif()
