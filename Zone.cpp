#include "Zone.h"

Zone::Zone(int id) {
    this->zoneId = id;
    this->areaCount = 3; // Standard 3 areas per zone
    this->areas = new ParkingArea*[areaCount];
    for (int i = 0; i < areaCount; i++) {
        this->areas[i] = new ParkingArea(10); // 10 slots per area
    }
}

Zone::~Zone() {
    for (int i = 0; i < areaCount; i++) {
        delete areas[i];
    }
    delete[] areas;
}

ParkingArea* Zone::getArea(int index) {
    if (index >= 0 && index < areaCount) return areas[index];
    return nullptr;
}

int Zone::getAreaCount() {
    return areaCount;
}