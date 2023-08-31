//
//src/utils/log.cpp
//

#include "log.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>

void writeLog(const QString& operation, const QString& message, bool success) {
    QFile logFile("server.log");
    if (!logFile.open(QIODevice::Append | QIODevice::Text)) {
        return; // Failed to open log file
    }

    QTextStream out(&logFile);
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString status = success ? "Success" : "Failure";

    out << "[" << timestamp << "] [" << operation << "] [" << status << "] " << message << "\n";

    logFile.close();
}