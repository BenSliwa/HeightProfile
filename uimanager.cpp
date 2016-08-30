#include "uimanager.h"
#include <QQmlContext>

UiManager::UiManager(QObject *_parent) : QObject(_parent),
    m_angle(0)
{
    m_angle = 340;
    double distance_m = 10000;


    QQmlContext *context = m_qml.rootContext();
    context->setContextProperty("UiManager", this);
    context->setContextProperty("ElevationAPI", &m_api);

    m_qml.load(QUrl(QLatin1String("qrc:/main.qml")));

    QList<Position> positions;

    Position reference(7.028196, 51.463024);

    m_fileName = "angle" + QString::number(m_angle) + ".png";

    positions << reference;

    Position measurementpoint = m_api.getTargetPosition(reference, m_angle, distance_m);

    positions << measurementpoint;
    m_api.requestElevation(positions, 250);
}

QString UiManager::getFileName()
{
    return m_fileName;
}

double UiManager::getAngle()
{
    return m_angle;
}
