#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include "net/googleelevationapi.h"

class UiManager : public QObject
{
    Q_OBJECT
public:
    UiManager(QObject *_parent = 0);

    Q_INVOKABLE QString getFileName();
    Q_INVOKABLE double getAngle();

private:
    QQmlApplicationEngine m_qml;
    GoogleElevationAPI m_api;

    QString m_fileName;
    double m_angle;
};

#endif // UIMANAGER_H
