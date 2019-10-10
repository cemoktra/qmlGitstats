#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>
#include "src/repo.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QQuickWindow::setSceneGraphBackend(QSGRendererInterface::Direct3D12);
    
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    Repository repo;
    const QUrl url(QStringLiteral("qrc:/qml/Main.qml"));
    
    qmlRegisterType<QAbstractListModel>();
    qmlRegisterType<QSortFilterProxyModel>();
    qmlRegisterSingletonType( QUrl("qrc:/qml/Theme.qml"), "Theme", 1, 0, "Theme" );

    engine.rootContext()->setContextProperty("repoObj", &repo);
    engine.load(url);
    return app.exec();
}
