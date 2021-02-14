#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "timer.h"

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    app.setOrganizationName("Some Organization");
    app.setOrganizationDomain("Some Domain");
    QQmlApplicationEngine engine;
    Timer timer;
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("timer", &timer);
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    engine.load(url);
    return app.exec();
}
