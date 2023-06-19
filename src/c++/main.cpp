#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQuickWindow>
#include <QGuiApplication>
#include <QDateTime>
#include <QScreen>
#include <QDebug>


#include "filesystemmodel.h"

#if defined(Q_OS_WIN)
#include <windows.h>
#endif

int main(int argc, char *argv[]) {
#if defined(Q_OS_WIN)
    FreeConsole();
#endif
    QGuiApplication app(argc, argv);
    app.setOrganizationName("Radar-mms");
    app.setOrganizationDomain("radar-mms.com");
    app.setApplicationName("Eco Map");
    const QUrl qml_entry(QStringLiteral("qrc:/Main.qml"));
    QQmlEngine engine;
    QObject::connect(&engine, &QQmlEngine::quit, qApp, &QCoreApplication::quit);
    QQmlComponent component(&engine);
    QQuickWindow::setDefaultAlphaBuffer(true);
    component.loadUrl(qml_entry);
    FileSystemModel m;
    m.setNewPath("/home/user");
    if(component.isReady())
        component.create();
    else
    {
        qInstallMessageHandler(0);
        qCritical() << "FATAL QML ERROR: " << component.errorString();
    }
    return app.exec();
}
