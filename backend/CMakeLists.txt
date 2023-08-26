cmake_minimum_required(VERSION 3.26)
project(backend_new)

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


add_executable(backend_new
        src/include/db.h
        src/include/group.h
        src/include/message.h
        src/include/user.h
        src/bot/bot.cpp
        src/include/clustering.h
        src/include/connection.h
        src/include/encryption.h
        src/include/media.h
        src/include/recommendation.h
        src/include/server.h
        src/media/media.cpp
        src/recommendation/clustering.cpp
        src/recommendation/recommendation.cpp
        src/server/connection.cpp
        src/server/server.cpp
        src/utils/encryption.cpp
        src/main.cpp
        src/user.cpp
        src/message.cpp
        src/group.cpp
        src/Database/db.cpp
)

target_link_libraries(backend_new
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Network
        Qt::Sql # 链接 Sql 库
        sqlite3
)

include_directories(${PROJECT_SOURCE_DIR}/src/include)
