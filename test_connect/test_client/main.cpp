#include <QApplication>
#include <QTcpSocket>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QTcpSocket socket;

    // 连接到主机的 IP 地址和端口
    socket.connectToHost("127.0.0.1", 10043);

    // 检查连接是否成功
    if (socket.waitForConnected()) {
        qDebug() << "Connected to server!";
    } else {
        qDebug() << "Failed to connect:" << socket.errorString();
    }

    return app.exec();
}
