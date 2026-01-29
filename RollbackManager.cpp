#include "RollbackManager.h"

RollbackManager::RollbackManager() : top(-1) {}
RollbackManager::~RollbackManager() {
    while (top >= 0) delete history[top--];
}
void RollbackManager::pushAction(std::string vid, int z, int a, int s) {
    if (top < 99) {
        history[++top] = new RollbackAction{vid, z, a, s};
    }
}
RollbackAction* RollbackManager::popAction() {
    return (top >= 0) ? history[top--] : nullptr;
}