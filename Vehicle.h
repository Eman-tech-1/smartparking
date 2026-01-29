#ifndef VEHICLE_H
#define VEHICLE_H
#include <string>

class Vehicle {
private:
    std::string vehicleID, ownerName, cnic;
    int preferredZone;
public:
    Vehicle(std::string id, std::string name, std::string c, int zone);
    std::string getVehicleID();
    std::string getOwnerName();
    std::string getCNIC();
    int getPreferredZone();
};
#endif