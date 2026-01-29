#include "ParkingSystem.h"
#include <iostream>

ParkingSystem::ParkingSystem(int numZones) : totalZones(numZones), vehicleCount(0) {
    zones = new Zone*[numZones];
    for (int i = 0; i < numZones; i++) zones[i] = new Zone(i);
    rollbackMgr = new RollbackManager();
    for(int i=0; i<100; i++) parkedVehicles[i] = nullptr;
}

bool ParkingSystem::isVehicleAlreadyParked(std::string vid) {
    for (int i = 0; i < vehicleCount; i++) {
        if (parkedVehicles[i] != nullptr && parkedVehicles[i]->getVehicleID() == vid) return true;
    }
    return false;
}

int ParkingSystem::getZoneCount(int zoneIdx) {
    if (zoneIdx < 0 || zoneIdx >= totalZones) return 0;
    int count = 0;
    for (int j = 0; j < zones[zoneIdx]->getAreaCount(); j++) {
        ParkingArea* area = zones[zoneIdx]->getArea(j);
        for (int k = 0; k < area->getSlotCount(); k++) {
            if (!area->getSlot(k)->isAvailable()) count++;
        }
    }
    return count;
}

void ParkingSystem::processParking(Vehicle v) {
    int prefZone = v.getPreferredZone();
    Zone* z = zones[prefZone];
    for (int j = 0; j < z->getAreaCount(); j++) {
        ParkingArea* area = z->getArea(j);
        for (int k = 0; k < area->getSlotCount(); k++) {
            if (area->getSlot(k)->isAvailable()) {
                area->getSlot(k)->occupy(v.getVehicleID());
                rollbackMgr->pushAction(v.getVehicleID(), prefZone, j, k);
                // Add to table storage
                if (vehicleCount < 100) {
                    parkedVehicles[vehicleCount++] = new Vehicle(v.getVehicleID(), v.getOwnerName(), v.getCNIC(), v.getPreferredZone());
                }
                return;
            }
        }
    }
}

void ParkingSystem::performRollback() {
    RollbackAction* last = rollbackMgr->popAction();
    if (last != nullptr) {
        zones[last->zoneId]->getArea(last->areaId)->getSlot(last->slotId)->release();
        if (vehicleCount > 0) {
            delete parkedVehicles[--vehicleCount];
            parkedVehicles[vehicleCount] = nullptr;
        }
        delete last;
    }
}

int ParkingSystem::getVehicleCount() { return vehicleCount; }
Vehicle* ParkingSystem::getVehicleAt(int index) { return parkedVehicles[index]; }

ParkingSystem::~ParkingSystem() {
    for (int i = 0; i < totalZones; i++) delete zones[i];
    delete[] zones;
    delete rollbackMgr;
    for(int i=0; i<vehicleCount; i++) delete parkedVehicles[i];
}