#ifndef PARKINGREQUEST_H
#define PARKINGREQUEST_H
#include <string>

class ParkingRequest {
private:
    std::string status;
public:
    ParkingRequest();
    void updateStatus(std::string s);
};
#endif