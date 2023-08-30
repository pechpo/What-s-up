// src/main.cpp

#include <QApplication>
#include "server.h"
#include "db.h"
#include "log.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 设置服务器监听的 IP 地址和端口
    QString address = "0.0.0.0";
    quint16 port = 10043;

    // 创建并启动服务器
    Server server(address, port);

    if (server.start()) {
        writeLog("Server", "Server started at " + address + ":" + QString::number(port), true);
    } else {
        writeLog("Server", "Failed to start server at " + address + ":" + QString::number(port), false);
    }

    return QApplication::exec();
}