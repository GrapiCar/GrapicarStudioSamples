#include <iostream>
#include "grapi/runtime/action_instance.h"
#include "grapi/runtime/action.h"
#include "../src/AnimationAction.h"
#include "../src/AnimationOpacity.h"
#include "../src/AnimationSameController.h"
#include "../src/AnimationWithChild.h"
#include "../src/AnimationClamp.h"

namespace grapi::runtime {

Action* createActionInstance(const std::string& action_id) {
    Action* aa = nullptr;

    if (action_id == "b68053c6-6a2c-4cfc-bf4b-a61806f4219d") {
        AnimationAction* tmp = new AnimationAction(action_id);
        aa = tmp;
        return aa;
    }

    if (action_id == "d0546472-05d8-4b56-97dd-277c052f5c79") {
        AnimationOpacity* tmp = new AnimationOpacity(action_id);
        aa = tmp;
        return aa;
    }

    if (action_id == "f9127139-8e34-4751-a185-84661c3962bb") {
        AnimationSameController* tmp = new AnimationSameController(action_id);
        aa = tmp;
        return aa;
    }

    if (action_id == "dd3be48f-1315-4d3b-8cdb-a4d8cacb649f") {
        AnimationWithChild* tmp = new AnimationWithChild(action_id);
        aa = tmp;
        return aa;
    }

    if (action_id == "82367fbf-cc2e-451a-9002-c56c417b7806") {
        AnimationClamp* tmp = new AnimationClamp(action_id);
        aa = tmp;
        return aa;
    }

    return aa;
}

bool initActionInstance(Action* action) {
    if (action->getElementID() == "b68053c6-6a2c-4cfc-bf4b-a61806f4219d") {
        AnimationAction* tmp = static_cast<AnimationAction*>(action);
        return true;
    }
    if (action->getElementID() == "d0546472-05d8-4b56-97dd-277c052f5c79") {
        AnimationOpacity* tmp = static_cast<AnimationOpacity*>(action);
        return true;
    }
    if (action->getElementID() == "f9127139-8e34-4751-a185-84661c3962bb") {
        AnimationSameController* tmp = static_cast<AnimationSameController*>(action);
        return true;
    }
    if (action->getElementID() == "dd3be48f-1315-4d3b-8cdb-a4d8cacb649f") {
        AnimationWithChild* tmp = static_cast<AnimationWithChild*>(action);
        return true;
    }
    if (action->getElementID() == "82367fbf-cc2e-451a-9002-c56c417b7806") {
        AnimationClamp* tmp = static_cast<AnimationClamp*>(action);
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
