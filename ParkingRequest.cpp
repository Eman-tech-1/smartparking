#include "ParkingRequest.h"

ParkingRequest::ParkingRequest() : status("REQUESTED") {}
void ParkingRequest::updateStatus(std::string s) { status = s; }