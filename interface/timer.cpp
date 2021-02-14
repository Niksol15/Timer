#include "timer.h"
#include <QUrl>
#include <QRegularExpression>

namespace {
    const QRegularExpression timeFormat(QString("^[0-5](\\d?)(:[0-5](\\d)?(:\\d{1,3})?)?$"),
                                        QRegularExpression::NoPatternOption);
    constexpr char kDefaultAudioFileName[] = "qrc:/sound/beep.wav";
}

Timer::Timer(QObject *parent) : QObject(parent), timeOnTimer("Time"), mainTimer(new QTimer(this)),
                                frameTimer(new QTimer(this)), logger(), timeValidator(timeFormat), isTimeSet(false),
                                soundFileName(kDefaultAudioFileName), timeStamps() {
    mainTimer->setSingleShot(true);
    mainTimer->callOnTimeout(this, &Timer::TimeOut);
    frameTimer->callOnTimeout(this, &Timer::setCurrentTime);
    logger.logMessage("Timer Created");
}


QString Timer::time() {
    return timeOnTimer;
}

void Timer::setCurrentTime() {
    setTime(msecToQStr(mainTimer->remainingTime()));
}

void Timer::setTime(const QString &newTime) {
    timeOnTimer = newTime;
    emit timeChanged(newTime);
}

bool Timer::isActive() {
    return mainTimer->isActive();
}

void Timer::start() {
    if (!isTimeSet) {
        logger.logMessage("Initial time not set", Logger::LogLevel::CRITICAL);
        setTime("Input initial time");
        return;
    }
    logger.logMessage("Start");
    mainTimer->start();
    frameTimer->start(1);
    emit isActiveChanged(mainTimer->isActive());
}

void Timer::pause() {
    mainTimer->setInterval(mainTimer->remainingTime());
    mainTimer->stop();
    frameTimer->stop();
    logger.logMessage("Pause");
    emit isActiveChanged(mainTimer->isActive());
}

QString Timer::msecToQStr(int msec) {
    QString res(QString::number(msec / 60000));
    msec %= 60000;
    int sec = msec / 1000;
    res += (sec < 10 ? ":0" : ":") + QString::number(sec);
    msec %= 1000;
    QString temp;
    if (msec < 10) {
        temp = ":00";
    } else if (msec < 100) {
        temp = ":0";
    } else {
        temp = ":";
    }
    res += temp + QString::number(msec);
    return res;
}

void Timer::TimeOut() {
    frameTimer->stop();
    QSound::play(soundFileName);
    isTimeSet = false;
    setTime("Time Out");
    logger.logMessage("Time out");
    emit isActiveChanged(false);
}

void Timer::setAlarmSound(const QString &pathToSoundFile) {
    QUrl url(pathToSoundFile);
    if (url.isLocalFile()) {
        soundFileName = url.path();
        logger.logMessage("Set alarm sound: " + soundFileName);
    } else {
        logger.logMessage(pathToSoundFile + " - path is invalid", Logger::LogLevel::WARNING);
    }
}

void Timer::setInitialTime(const QString &newTime) {
    int pos = 0;
    QString temp = newTime;
    if (timeValidator.validate(temp, pos) == QValidator::Acceptable) {
        while (temp.count(':') < 2) {
            temp += ":0";
        }
        QStringList parts = temp.split(':');
        int msecInitialTime = parts[0].toInt() * 60 * 1000 + parts[1].toInt() * 1000 + parts[2].toInt();
        mainTimer->setInterval(msecInitialTime);
        QString qstrInitialTime = msecToQStr(msecInitialTime);
        setTime(qstrInitialTime);
        isTimeSet = true;
        timeStamps.clear();
        emit timeStampsModelChanged(timeStamps);
        logger.logMessage("Set initial time: " + qstrInitialTime);
    } else {
        isTimeSet = false;
        setTime("Incorrect time format");
        logger.logMessage("Input incorrect initial time: " + newTime, Logger::LogLevel::WARNING);
    }
}

void Timer::reset() {
    isTimeSet = false;
    setTime("Time");
    timeStamps.clear();
    emit timeStampsModelChanged(timeStamps);
    logger.logMessage("Reset");
}

void Timer::tap() {
    logger.logMessage("tap timestamp: " + msecToQStr(mainTimer->remainingTime()));
    timeStamps.append(msecToQStr(mainTimer->remainingTime()));
    emit timeStampsModelChanged(timeStamps);
}

QStringList Timer::timeStampsModel() {
    return timeStamps;
}

