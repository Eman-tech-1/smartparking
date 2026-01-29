#ifndef PARKINGSYSTEM_H
#define PARKINGSYSTEM_H

#include "Zone.h"
#include "RollbackManager.h"
#include "Vehicle.h"
#include <string>

class ParkingSystem {
private:
    Zone** zones;
    int totalZones;
    RollbackManager* rollbackMgr;
    Vehicle* parkedVehicles[100]; // Fixed array for table data
    int vehicleCount;

public:
    ParkingSystem(int numZones);
    ~ParkingSystem();
    void processParking(Vehicle v);
    void performRollback();
    bool isVehicleAlreadyParked(std::string vid);
    int getZoneCount(int zoneIdx);
    int getVehicleCount();
    Vehicle* getVehicleAt(int index);
};
#endif