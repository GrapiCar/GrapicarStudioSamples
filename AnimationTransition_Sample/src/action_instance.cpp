#include <iostream>
#include "grapi/runtime/action_instance.h"
#include "grapi/runtime/action.h"
#include "../src/AnimatorStateMachine.h"
#include "grapi/runtime/utils.h"
#include "grapi/runtime/animator.h"

namespace grapi::runtime {

Action* createActionInstance(const std::string& action_id) {
    Action* aa = nullptr;

    if (action_id == "8b808f4d-a628-461c-b14a-db401c346dfe") {
        AnimatorStateMachine* tmp = new AnimatorStateMachine(action_id);
        aa = tmp;
        return aa;
    }

    return aa;
}

bool initActionInstance(Action* action) {
    if (action->getElementID() == "8b808f4d-a628-461c-b14a-db401c346dfe") {
        AnimatorStateMachine* tmp = static_cast<AnimatorStateMachine*>(action);
        tmp->animator = findComponentByObjId<grapi::runtime::Animator>("beb72eca-df8b-4200-a828-8a9eee7e0fe9");
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
