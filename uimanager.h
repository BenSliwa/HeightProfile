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

private:
    QQmlApplicationEngine m_qml;
    GoogleElevationAPI m_api;
};

#endif // UIMANAGER_H
