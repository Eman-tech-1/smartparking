#ifndef ALLOCATIONENGINE_H
#define ALLOCATIONENGINE_H
#include "Zone.h"
#include "ParkingRequest.h"

class AllocationEngine {
public:
    bool allocateSlot(Zone* zones, int zoneCount, int prefZone, ParkingRequest& req);
};

#endif