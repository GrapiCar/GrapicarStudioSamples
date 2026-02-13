#include <iostream>
#include "grapi/runtime/action_instance.h"
#include "grapi/runtime/action.h"
#include "../src/speed_needle_pivot.h"
#include "../src/speed_number.h"
#include "grapi/runtime/utils.h"

namespace grapi::runtime {

Action* createActionInstance(const std::string& action_id) {
    Action* aa = nullptr;

    if (action_id == "345c8cf2-afed-4ae1-8f17-11767f5b6df9") {
        speed_needle_pivot* tmp = new speed_needle_pivot(action_id);
        aa = tmp;
        return aa;
    }

    if (action_id == "f01afcce-30d1-47a2-8ab6-a6cef3b035b0") {
        speed_number* tmp = new speed_number(action_id);
        aa = tmp;
        return aa;
    }

    return aa;
}

bool initActionInstance(Action* action) {
    if (action->getElementID() == "345c8cf2-afed-4ae1-8f17-11767f5b6df9") {
        speed_needle_pivot* tmp = static_cast<speed_needle_pivot*>(action);
        tmp->pivot = findObjectById("59b6aa69-4661-4789-9461-0d6a10a14c6b");
        return true;
    }
    if (action->getElementID() == "f01afcce-30d1-47a2-8ab6-a6cef3b035b0") {
        speed_number* tmp = static_cast<speed_number*>(action);
        tmp->position_adjusted_ = false;
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
