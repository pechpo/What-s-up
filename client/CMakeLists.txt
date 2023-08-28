cmake_minimum_required(VERSION 3.5)

project(client VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt6 COMPONENTS Network REQUIRED)
set(TS_FILES client_zh_CN.ts)

set(PROJECT_SOURCES
        main.cpp



        ${TS_FILES}
)

qt_add_executable(client
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    director/director.h director/director.cpp
    network/connection.h network/connection.cpp
    ui/loginwindow.h ui/loginwindow.cpp
    ui/loginwindow.h ui/loginwindow.cpp ui/loginwindow.ui
    ui/logindialog.h ui/logindialog.cpp ui/logindialog.ui
    ui/UI-images.qrc
    ui/mainwindow.h ui/mainwindow.cpp ui/mainwindow.ui
    ui/chatwindow.h ui/chatwindow.cpp ui/chatwindow.ui
    ui/profilebar.h ui/profilebar.cpp ui/profilebar.ui
    ui/registerdialog.h ui/registerdialog.cpp ui/registerdialog.ui





)


target_link_libraries(client PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(client PRIVATE Qt6::Network)

include_directories(./)

set_target_properties(client PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS client
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(client)
endif()
