cmake_minimum_required(VERSION 3.16)

project(FilmManager VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(FilmManager
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        startviewwidget.h startviewwidget.cpp startviewwidget.ui
        peoplelistviewwidget.h peoplelistviewwidget.cpp peoplelistviewwidget.ui
        personviewwidget.h personviewwidget.cpp personviewwidget.ui
        addpersondialog.h addpersondialog.cpp addpersondialog.ui
        modifypersondialog.h modifypersondialog.cpp modifypersondialog.ui
        movielistviewwidget.h movielistviewwidget.cpp movielistviewwidget.ui
        addmoviedialog.h addmoviedialog.cpp addmoviedialog.ui
        movieviewwidget.h movieviewwidget.cpp movieviewwidget.ui
        modifymoviedialog.h modifymoviedialog.cpp modifymoviedialog.ui
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET FilmManager APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(FilmManager SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(FilmManager
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(FilmManager PRIVATE Qt${QT_VERSION_MAJOR}::Widgets FilmManager_Domain)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.FilmManager)
endif()
set_target_properties(FilmManager PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS FilmManager
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(FilmManager)
endif()
add_subdirectory(FilmManager_Domain)
