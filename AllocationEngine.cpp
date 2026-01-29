#include "AllocationEngine.h"

bool AllocationEngine::allocateSlot(Zone* zones, int zoneCount, int prefZone, ParkingRequest& req) {
    // [cite: 56] Same-zone preference
    for(int a = 0; a < zones[prefZone].areaCount; a++) {
        for(int s = 0; s < zones[prefZone].areas[a].slotCount; s++) {
            if(zones[prefZone].areas[a].slots[s].isAvailable) { // [cite: 57]
                zones[prefZone].areas[a].slots[s].isAvailable = false;
                req.areaIdx = a;
                req.slotIdx = s;
                req.requestedZone = prefZone;
                req.transitionTo(ALLOCATED);
                return true;
            }
        }
    }
    // [cite: 60] Logic for cross-zone allocation would follow here
    return false;
}