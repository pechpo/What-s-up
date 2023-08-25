cmake_minimum_required(VERSION 3.26)
project(test_client)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/home/zixin/Qt/6.5.2/gcc_64")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Network
        REQUIRED)

add_executable(test_client main.cpp)
target_link_libraries(test_client
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Network
)

