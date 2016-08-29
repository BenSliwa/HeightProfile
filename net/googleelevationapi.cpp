#include "googleelevationapi.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

GoogleElevationAPI::GoogleElevationAPI(QObject *_parent) : QObject(_parent)
{

}

void GoogleElevationAPI::requestElevation(const QList<Position> &_positions)
{
    QString url = "https://maps.googleapis.com/maps/api/elevation/json?path=";
    for(int i=0; i<_positions.size(); i++)
    {
        Position position = _positions.at(i);
        url += QString::number(position.latitude) + "," + QString::number(position.longitude);
        if(i<_positions.size()-1)
            url += "|";
    }
    url += "&samples=5";

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

        for(int i=0; i<array.size(); i++)
        {
            QMap<QString, QVariant> map = array.at(i).toVariant().toMap();
            double elevation = map.value("elevation").toDouble();

            QMap<QString, QVariant> location = map.value("location").toMap();
            double latitude = location.value("lat").toDouble();
            double longitude = location.value("lng").toDouble();

            Position position = Position(longitude, latitude, elevation);
            positions << position;

            position.info();

            //heightProfile << elevation;

            QMap<QString, QVariant> entry;
            entry.insert("longitude", longitude);
            entry.insert("latitude", latitude);
            entry.insert("elevation", elevation);
            heightProfile << entry;
        }

        emit heightProfileReceived(heightProfile);
    }
}
