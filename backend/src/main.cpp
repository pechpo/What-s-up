// src/main.cpp

#include <QApplication>
#include "server.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 设置服务器监听的 IP 地址和端口
    QString address = "0.0.0.0";
    quint16 port = 10043;

    // 创建并启动服务器
    Server server(address, port);
    server.start();

    return QApplication::exec();
}
