cmake_minimum_required(VERSION 3.26)
project(What_s_up)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Network
        Sql # 添加 Sql 组件
        REQUIRED)

add_executable(What_s_up
        src/main.cpp
        src/server/server.cpp
        src/server/connection.cpp
        src/database/db_connection.cpp
        src/database/user.cpp
        src/database/group.cpp
        src/database/message.cpp
        src/recommendation/clustering.cpp
        src/recommendation/recommendation.cpp
        src/bot/bot.cpp
        src/media/media.cpp
        src/utils/encryption.cpp
        src/include/server.h
        src/include/user.h
        src/include/recommendation.h
        src/include/bot.h
        src/include/media.h
        src/include/encryption.h
        src/include/message.h
        src/include/db_connection.h
        src/include/group.h
        src/include/clustering.h
        src/include/connection.h)

target_link_libraries(What_s_up
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Network
        Qt::Sql # 链接 Sql 库
        sqlite3
)

include_directories(${PROJECT_SOURCE_DIR}/src/include)
