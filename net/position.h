#ifndef POSITION_H
#define POSITION_H


class Position
{
public:
    Position(double _longitude = 0, double _latitude = 0, double _altitude = 0);

    void info();

public:
    double longitude;
    double latitude;
    double altitude;
};

#endif // POSITION_H
