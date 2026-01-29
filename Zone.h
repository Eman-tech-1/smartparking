#ifndef ZONE_H
#define ZONE_H

#include "ParkingArea.h"

class Zone {
private:
    ParkingArea** areas;
    int areaCount;
    int zoneId;

public:
    Zone(int id); // This constructor was missing!
    ~Zone();
    ParkingArea* getArea(int index);
    int getAreaCount();
};

#endif