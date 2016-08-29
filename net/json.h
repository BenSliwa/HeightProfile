#ifndef JSON_H
#define JSON_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

class JSON : public QObject
{
    Q_OBJECT
public:
    JSON(QObject *_parent = 0);
};

#endif // JSON_H
