#include <QtGui>
#include <QtQml>
#include <QTime>

class CurrentTime {
public:
    QString value(){
        return QTime::currentTime().toString();
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    CurrentTime current;

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.rootContext()->setContextProperty("current", current.value());
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    Sleep(2000);
    engine.rootContext()->setContextProperty("current", current.value());

    return app.exec();
}
