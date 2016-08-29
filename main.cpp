#include <QGuiApplication>
#include "uimanager.h"
#include "net/googleelevationapi.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);


    UiManager ui;




    return app.exec();
}
