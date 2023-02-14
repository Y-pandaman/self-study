#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QScreen>
#include "myobject.h"
#include <QObject>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect rect = screen->virtualGeometry();

     // WINDOW_WIDTH为全局属性，qml文件中可使用
    context->setContextProperty("WINDOW_WIDTH", rect.width());
//    context->setContextProperty("WINDOW_WIDTH", 200);
//    qmlRegisterType<MyObject>("MyObj", 1, 0, "MyObject");  // 方法一：一定通过创建对象来定义自定义的object
    qmlRegisterSingletonInstance("MyObj", 1, 0, "MyObject", MyObject::getInstance());  // 方法二：单例法

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    // C++端绑定信号与槽
    // engine 加载完成后， load以后
    engine.rootObjects();
    auto list = engine.rootObjects();
    auto window = list.first();  // 获取根目录的objectName
//    auto buttonObj = list.first()->findChild<QObject *>("myButton");  // 获取子控件的objectName
    QObject::connect(window, SIGNAL(qmlSig(int, QString)), MyObject::getInstance(), SLOT(cppSlot(int, QString)));
    QObject::connect(MyObject::getInstance(), SIGNAL(cppSig(QVariant, QVariant)), window, SLOT(qmlSlot(QVariant, QVariant)));

    // C++直接访问qml函数，使用QMetaObject::invokeMethod方法
    QVariant res;
    QVariant arg1 = 123;
    QVariant arg2 = "abc";
    QMetaObject::invokeMethod(window, "qmlFunc", Q_RETURN_ARG(QVariant, res), Q_ARG(QVariant, arg1), Q_ARG(QVariant, arg2));
    qDebug() << "res = " << res;
    return app.exec();
}
