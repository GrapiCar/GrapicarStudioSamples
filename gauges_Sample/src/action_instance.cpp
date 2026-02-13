#include <iostream>
#include "grapi/runtime/action_instance.h"
#include "grapi/runtime/action.h"
#include "../src/fuel.h"
#include "grapi/runtime/utils.h"

namespace grapi::runtime {

Action* createActionInstance(const std::string& action_id) {
    Action* aa = nullptr;

    if (action_id == "306146d8-0869-491d-8c8e-0b8b8bdf698c") {
        fuel* tmp = new fuel(action_id);
        aa = tmp;
        return aa;
    }

    return aa;
}

bool initActionInstance(Action* action) {
    if (action->getElementID() == "306146d8-0869-491d-8c8e-0b8b8bdf698c") {
        fuel* tmp = static_cast<fuel*>(action);
        tmp->gauge = findObjectById("f29b7ec2-b455-4c46-9988-6089a2e55c1e");
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
