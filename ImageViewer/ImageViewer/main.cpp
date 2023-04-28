#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include "ImageProcessor.h"
#include "ImageProvider.h"

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    ImageProvider* liveImageProvider(new ImageProvider);

    auto context = engine.rootContext();

    ImageProcessor imageProcessor;
    engine.rootContext()->setContextProperty("ImageProcessor", &imageProcessor);
    engine.rootContext()->setContextProperty("liveImageProvider", liveImageProvider);

    engine.addImageProvider(QLatin1String("live"), liveImageProvider);

    QObject::connect(&imageProcessor, &ImageProcessor::newImage, liveImageProvider, &ImageProvider::updateImage);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    QQuickStyle::setStyle("Fusion");



    return app.exec();
}
