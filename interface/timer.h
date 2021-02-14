#ifndef TIMER_H
#define TIMER_H

#include "logger.h"
#include <QObject>
#include <QScopedPointer>
#include <QTimer>
#include <QtMultimedia/QSound>
#include <QRegularExpressionValidator>
#include <QStringList>

class Timer : public QObject{
    Q_OBJECT
    Q_PROPERTY(QString time READ time WRITE setInitialTime NOTIFY timeChanged)
    Q_PROPERTY(bool isActive READ isActive NOTIFY isActiveChanged)
    Q_PROPERTY(QStringList timeStampsModel READ timeStampsModel NOTIFY timeStampsModelChanged)
public:
    explicit Timer(QObject *parent = nullptr);
    Q_INVOKABLE void setAlarmSound(const QString& pathToSoundFile);
    Q_INVOKABLE void start();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void reset();
    Q_INVOKABLE void tap();
    bool isActive();
    QString time();
    QStringList timeStampsModel();
signals:
    void timeChanged(const QString& time);
    void isActiveChanged(bool newState);
    void timeStampsModelChanged(const QStringList& stamps);
public slots:
    void setInitialTime(const QString& newTime);
    void TimeOut();
private slots:
    void setCurrentTime();
private:
    QString timeOnTimer;
    QScopedPointer<QTimer> mainTimer;
    QScopedPointer<QTimer> frameTimer;
    Logger logger;  
    QRegularExpressionValidator timeValidator;
    bool isTimeSet;
    QString soundFileName;
    QStringList timeStamps;
    QString msecToQStr(int msec);
    void setTime(const QString& newTime);   
};

#endif // TIMER_H
