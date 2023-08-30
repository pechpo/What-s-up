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

find_package(CURL REQUIRED)

add_executable(backend
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
        src/database/user.cpp
        src/database/message.cpp
        src/database/group.cpp
        src/database/db.cpp
        src/include/handle.h
        src/handle/handle.cpp
        src/handle/handle_user.cpp
        src/handle/handle_group.cpp
        src/handle/handle_message.cpp
)

target_link_libraries(backend
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Network
        Qt::Sql
)

target_link_libraries(backend ${CURL_LIBRARIES})

include_directories(${PROJECT_SOURCE_DIR}/src/include)