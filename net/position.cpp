#include "position.h"
#include <QDebug>

Position::Position(double _longitude, double _latitude, double _altitude) :
    longitude(_longitude),
    latitude(_latitude),
    altitude(_altitude)
{

}

void Position::info()
{
    qDebug() << longitude << latitude << altitude;
}
