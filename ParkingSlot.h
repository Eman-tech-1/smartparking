#ifndef PARKINGSLOT_H
#define PARKINGSLOT_H
#include <string>

class ParkingSlot {
private:
    bool available;
    std::string vehicleID;
public:
    ParkingSlot();
    bool isAvailable();
    std::string getVehicleID();
    void occupy(std::string vid);
    void release();
};
#endif