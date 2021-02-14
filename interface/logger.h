#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <QFile>

class Logger {
public:
    Logger();
    enum class LogLevel{
        INFO,
        DEBUG,
        WARNING,
        CRITICAL
    };
    void logMessage(const QString& message, LogLevel level = LogLevel::INFO);
    ~Logger();
private:
    const QString LOG_FILE_NAME = "timer.log";
    QFile logFile;
    static QString LogLvlToQStr(LogLevel loglvl);
};

#endif // LOGGER_H
