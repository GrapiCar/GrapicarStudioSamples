#include <iostream>
#include "grapi/runtime/action_instance.h"
#include "grapi/runtime/action.h"
#include "../src/first.h"
#include "../src/second.h"
#include "../src/third.h"
#include "../src/four.h"

namespace grapi::runtime {

Action* createActionInstance(const std::string& action_id) {
    Action* aa = nullptr;

    if (action_id == "f83f61f0-8cca-45b6-afb0-6a8fdb3e8095") {
        first* tmp = new first(action_id);
        aa = tmp;
        return aa;
    }

    if (action_id == "514c846e-cdec-4454-a8b7-dd576ef34f53") {
        second* tmp = new second(action_id);
        aa = tmp;
        return aa;
    }

    if (action_id == "22fe9756-8ff8-48c9-913b-a61c63196db1") {
        third* tmp = new third(action_id);
        aa = tmp;
        return aa;
    }

    if (action_id == "39cd893a-d295-4849-9adc-97c4e4a25c5d") {
        four* tmp = new four(action_id);
        aa = tmp;
        return aa;
    }

    return aa;
}

bool initActionInstance(Action* action) {
    if (action->getElementID() == "f83f61f0-8cca-45b6-afb0-6a8fdb3e8095") {
        first* tmp = static_cast<first*>(action);
        return true;
    }
    if (action->getElementID() == "514c846e-cdec-4454-a8b7-dd576ef34f53") {
        second* tmp = static_cast<second*>(action);
        return true;
    }
    if (action->getElementID() == "22fe9756-8ff8-48c9-913b-a61c63196db1") {
        third* tmp = static_cast<third*>(action);
        return true;
    }
    if (action->getElementID() == "39cd893a-d295-4849-9adc-97c4e4a25c5d") {
        four* tmp = static_cast<four*>(action);
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
