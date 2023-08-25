#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QTcpServer server;

    // 当有新的连接时创建一个新的 socket
    QObject::connect(&server, &QTcpServer::newConnection, [&server]() {
        QTcpSocket *socket = server.nextPendingConnection();
        qDebug() << "Client connected:" << socket->peerAddress().toString();
    });

    // 开始侦听端口 10043
    if (server.listen(QHostAddress::Any, 10043)) {
        qDebug() << "Server started on port 10043";
    } else {
        qDebug() << "Failed to start server:" << server.errorString();
        return 1;
    }

    return app.exec();
}
