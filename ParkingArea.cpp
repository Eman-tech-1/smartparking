#include "ParkingArea.h"

ParkingArea::ParkingArea(int count) {
    this->slotCount = count;
    this->slots = new ParkingSlot*[slotCount];
    for (int i = 0; i < slotCount; i++) {
        this->slots[i] = new ParkingSlot();
    }
}

ParkingArea::~ParkingArea() {
    for (int i = 0; i < slotCount; i++) {
        delete slots[i];
    }
    delete[] slots;
}

ParkingSlot* ParkingArea::getSlot(int index) {
    if (index >= 0 && index < slotCount) return slots[index];
    return nullptr;
}

int ParkingArea::getSlotCount() {
    return slotCount;
}