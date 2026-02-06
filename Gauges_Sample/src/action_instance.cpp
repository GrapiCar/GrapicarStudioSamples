#include <iostream>
#include "grapi/runtime/action_instance.h"
#include "grapi/runtime/action.h"
#include "../src/LeftGauge.h"
#include "../src/RightGauge.h"

namespace grapi::runtime {

Action* createActionInstance(const std::string& action_id) {
    Action* aa = nullptr;

    if (action_id == "57a3e6ed-ebe1-4f4b-9f6f-98e72dfc65f7") {
        LeftGauge* tmp = new LeftGauge(action_id);
        aa = tmp;
        return aa;
    }

    if (action_id == "e79cf4c1-e258-4ca1-bd26-441df09d0493") {
        RightGauge* tmp = new RightGauge(action_id);
        aa = tmp;
        return aa;
    }

    return aa;
}

bool initActionInstance(Action* action) {
    if (action->getElementID() == "57a3e6ed-ebe1-4f4b-9f6f-98e72dfc65f7") {
        LeftGauge* tmp = static_cast<LeftGauge*>(action);
        return true;
    }
    if (action->getElementID() == "e79cf4c1-e258-4ca1-bd26-441df09d0493") {
        RightGauge* tmp = static_cast<RightGauge*>(action);
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
