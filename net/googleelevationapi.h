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

    void requestElevation(const QList<Position> &_positions, int _samples);

    Position getTargetPosition(Position _position, double _angle, double _distance_m);

private:
    static double radToGrad(double _rad);
    static double gradToRad(double _grad);


public slots:
    void onElevationReply();

signals:
    void heightProfileReceived(const QVariantList &_heightProfile, double _minElevation, double _maxElevation, double _maxDistance);

private:
    QNetworkAccessManager m_http;
};

#endif // GOOGLEELEVATIONAPI_H
