#ifndef ROLLBACKMANAGER_H
#define ROLLBACKMANAGER_H
#include <string>

struct RollbackAction {
    std::string vehicleId;
    int zoneId, areaId, slotId;
};

class RollbackManager {
private:
    RollbackAction* history[100]; 
    int top;
public:
    RollbackManager();
    ~RollbackManager();
    void pushAction(std::string vid, int z, int a, int s);
    RollbackAction* popAction();
};
#endif