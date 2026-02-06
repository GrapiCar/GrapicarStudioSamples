#include <iostream>
#include "grapi/runtime/action_instance.h"
#include "grapi/runtime/action.h"
#include "../src/Cluster.h"

namespace grapi::runtime {

Action* createActionInstance(const std::string& action_id) {
    Action* aa = nullptr;

    if (action_id == "e50b9f3f-73ad-438c-8a91-09ae79f5949b") {
        Cluster* tmp = new Cluster(action_id);
        aa = tmp;
        return aa;
    }

    return aa;
}

bool initActionInstance(Action* action) {
    if (action->getElementID() == "e50b9f3f-73ad-438c-8a91-09ae79f5949b") {
        Cluster* tmp = static_cast<Cluster*>(action);
        tmp->isTransitioning = false;
        tmp->prev_m_ = false;
        return true;
    }
    else {
        std::cerr << "Error: Unknown action ID: " << action->getElementID() << std::endl;
        return false;
    }
    return true;
}

Action* createPrefabActionInstance(const std::string& action_id) {
    Action* aa = nullptr;

    return aa;
}

bool initPrefabActionInstance(Action* action) {
    return true;
}

}  // namespace grapi::runtime
