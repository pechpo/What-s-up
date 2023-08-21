cmake_minimum_required(VERSION 3.26)
project(23_wechat)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(23_wechat main.cpp)
target_link_libraries(23_wechat
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

