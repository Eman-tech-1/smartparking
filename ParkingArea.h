#ifndef PARKINGAREA_H
#define PARKINGAREA_H

#include "ParkingSlot.h"

class ParkingArea {
private:
    ParkingSlot** slots;
    int slotCount;

public:
    ParkingArea(int count);
    ~ParkingArea();
    ParkingSlot* getSlot(int index); // Compiler needs this
    int getSlotCount();
};

#endif