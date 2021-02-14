#include "logger.h"

QString Logger::LogLvlToQStr(LogLevel loglvl){
    switch (loglvl) {
    case LogLevel::INFO:
        return "Info: ";
    case LogLevel::DEBUG:
        return "Debug: ";
    case LogLevel::WARNING:
        return "Warning: ";
    case LogLevel::CRITICAL:
        return "Critical: ";
    default:
        return "Unexpected: ";
    }
}

Logger::Logger(): logFile(LOG_FILE_NAME){
    logFile.open(QIODevice::WriteOnly);
}

void Logger::logMessage(const QString &message, LogLevel level){
    logFile.write((LogLvlToQStr(level) + message + "\n").toUtf8());
}

Logger::~Logger(){
    logFile.close();
}
