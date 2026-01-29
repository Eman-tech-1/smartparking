#include "Vehicle.h"

Vehicle::Vehicle(std::string id, std::string name, std::string c, int zone) 
    : vehicleID(id), ownerName(name), cnic(c), preferredZone(zone) {}

std::string Vehicle::getVehicleID() { return vehicleID; }
std::string Vehicle::getOwnerName() { return ownerName; }
std::string Vehicle::getCNIC() { return cnic; }
int Vehicle::getPreferredZone() { return preferredZone; }