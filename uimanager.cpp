#include "uimanager.h"
#include <QQmlContext>

UiManager::UiManager(QObject *_parent) : QObject(_parent)
{
    QQmlContext *context = m_qml.rootContext();
    context->setContextProperty("UiManager", this);
    context->setContextProperty("ElevationAPI", &m_api);

    m_qml.load(QUrl(QLatin1String("qrc:/main.qml")));

    QList<Position> positions;
    positions << Position(7.45, 51);
    positions << Position(7.45, 53);
    m_api.requestElevation(positions);
}
