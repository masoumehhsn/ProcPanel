#include <QApplication>
#include <QQmlApplicationEngine>
#include <procmanager.h>
#include <QTimer>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ProcManager procManager;

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.rootContext()->setContextProperty("procManager", &procManager);
    engine.loadFromModule("ProcPanel", "Main");

    return QCoreApplication::exec();
}
