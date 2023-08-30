#ifndef LOG_H
#define LOG_H

#include <QString>

void writeLog(const QString& operation, const QString& message, bool success);

#endif // LOG_H