cmake_minimum_required(VERSION 3.26)
project(backend)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Network
        Sql
        REQUIRED)

add_executable(backend
        src/include/db.h
        src/include/chat.h
        src/include/message.h
        src/include/user.h
        src/bot/bot.cpp
        src/include/clustering.h
        src/include/connection.h
        src/include/media.h
        src/include/log.h
        src/include/recommendation.h
        src/include/server.h
        src/media/media.cpp
        src/recommendation/clustering.cpp
        src/recommendation/recommendation.cpp
        src/server/connection.cpp
        src/server/server.cpp
        src/utils/log.cpp
        src/main.cpp
        src/database/user.cpp
        src/database/message.cpp
        src/database/chat.cpp
        src/database/db.cpp
        src/include/handle.h
        src/handle/handle.cpp
        src/handle/handle_user.cpp
        src/handle/handle_chat.cpp
        src/handle/handle_message.cpp
)

target_link_libraries(backend
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Network
        Qt::Sql
)

include_directories(${PROJECT_SOURCE_DIR}/src/include)
