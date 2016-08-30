#include "googleelevationapi.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <limits>
#include <iomanip>
#include <cmath>

GoogleElevationAPI::GoogleElevationAPI(QObject *_parent) : QObject(_parent)
{

}

void GoogleElevationAPI::requestElevation(const QList<Position> &_positions, int _samples)
{
    QString url = "http://maps.googleapis.com/maps/api/elevation/json?path=";
    for(int i=0; i<_positions.size(); i++)
    {
        Position position = _positions.at(i);
        url += QString::number(position.latitude) + "," + QString::number(position.longitude);
        if(i<_positions.size()-1)
            url += "|";
    }
    url += "&samples=" + QString::number(_samples);

    QNetworkRequest request;
    request.setUrl(QUrl(url));

    QNetworkReply *reply = m_http.get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(onElevationReply()));

    qDebug() << url;
}

void GoogleElevationAPI::onElevationReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    if(reply)
    {
        QByteArray rawData = reply->readAll();

        QJsonDocument document = QJsonDocument::fromJson(rawData);
        QJsonObject object = document.object();
        QJsonArray array = object.value("results").toArray();

        QList<Position> positions;

        QVariantList heightProfile;

        double minElevation = std::numeric_limits<double>::max();
        double maxElevation = std::numeric_limits<double>::min();
        for(int i=0; i<array.size(); i++)
        {
            QMap<QString, QVariant> map = array.at(i).toVariant().toMap();
            double elevation = map.value("elevation").toDouble();

            QMap<QString, QVariant> location = map.value("location").toMap();
            double latitude = location.value("lat").toDouble();
            double longitude = location.value("lng").toDouble();

            Position position = Position(longitude, latitude, elevation);
            positions << position;

            //position.info();

            //heightProfile << elevation;

            QMap<QString, QVariant> entry;
            entry.insert("longitude", longitude);
            entry.insert("latitude", latitude);
            entry.insert("elevation", elevation);
            heightProfile << entry;

            if(elevation<minElevation)
                minElevation = elevation;
            if(elevation>maxElevation)
                maxElevation = elevation;
        }

        double maxDistance = 10000;
        minElevation = 0;

        emit heightProfileReceived(heightProfile, minElevation, maxElevation, maxDistance);
    }
}

Position GoogleElevationAPI::getTargetPosition(Position _position, double _angle, double _distance_m)
{
    double yaw = fmod(_angle, 360);

    std::setprecision(10);
    double d = _distance_m/1000;
    double R = 6371;
    double h = gradToRad(yaw);
    double lat = gradToRad(_position.latitude);
    double lon = gradToRad(_position.longitude);
    double latitude = asin(sin(lat)*cos(d/R) + cos(lat)*sin(d/R)*cos(h));
    double longitude = lon + atan2(sin(h)*sin(d/R)*cos(lat), cos(d/R)-sin(lat)*sin(latitude));

    Position position = Position(radToGrad(longitude), radToGrad(latitude));

    return position;
}

double GoogleElevationAPI::radToGrad(double _rad)
{
    return (_rad*180/3.14159265358979323846);
}

double GoogleElevationAPI::gradToRad(double _grad)
{
    return _grad*3.14159265358979323846/180;
}
