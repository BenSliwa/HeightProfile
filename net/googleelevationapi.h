#ifndef GOOGLEELEVATIONAPI_H
#define GOOGLEELEVATIONAPI_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QList>

#include "position.h"

class GoogleElevationAPI : public QObject
{
    Q_OBJECT
public:
    GoogleElevationAPI(QObject *_parent = 0);

    void requestElevation(const QList<Position> &_positions);

public slots:
    void onElevationReply();

signals:
    void elevationReplyReceived(const QList<Position> &_positions);

private:
    QNetworkAccessManager m_http;
};

#endif // GOOGLEELEVATIONAPI_H
