#include "ParkingSlot.h"

ParkingSlot::ParkingSlot() : available(true), vehicleID("") {}
bool ParkingSlot::isAvailable() { return available; }
std::string ParkingSlot::getVehicleID() { return vehicleID; }
void ParkingSlot::occupy(std::string vid) { available = false; vehicleID = vid; }
void ParkingSlot::release() { available = true; vehicleID = ""; }