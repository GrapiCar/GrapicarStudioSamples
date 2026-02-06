#include <iostream>
#include "grapi/runtime/action_instance.h"
#include "grapi/runtime/action.h"
#include "../src/cell01.h"
#include "../src/cell02.h"
#include "../src/cell03.h"

namespace grapi::runtime {

Action* createActionInstance(const std::string& action_id) {
    Action* aa = nullptr;

    if (action_id == "b50f8b78-e0d6-494d-94b5-9449118e5415") {
        cell01* tmp = new cell01(action_id);
        aa = tmp;
        return aa;
    }

    if (action_id == "11d13c20-3ca8-4205-b990-31671c9661d9") {
        cell02* tmp = new cell02(action_id);
        aa = tmp;
        return aa;
    }

    if (action_id == "918258d6-86bf-4b11-a301-42e69a4384b7") {
        cell03* tmp = new cell03(action_id);
        aa = tmp;
        return aa;
    }

    return aa;
}

bool initActionInstance(Action* action) {
    if (action->getElementID() == "b50f8b78-e0d6-494d-94b5-9449118e5415") {
        cell01* tmp = static_cast<cell01*>(action);
        return true;
    }
    if (action->getElementID() == "11d13c20-3ca8-4205-b990-31671c9661d9") {
        cell02* tmp = static_cast<cell02*>(action);
        return true;
    }
    if (action->getElementID() == "918258d6-86bf-4b11-a301-42e69a4384b7") {
        cell03* tmp = static_cast<cell03*>(action);
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
