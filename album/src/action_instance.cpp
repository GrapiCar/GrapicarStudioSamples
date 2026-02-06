#include <iostream>
#include "grapi/runtime/action_instance.h"
#include "grapi/runtime/action.h"
#include "../src/album.h"

namespace grapi::runtime {

Action* createActionInstance(const std::string& action_id) {
    Action* aa = nullptr;

    if (action_id == "17514f4f-ea32-4867-aa04-18f23887b55b") {
        album* tmp = new album(action_id);
        aa = tmp;
        return aa;
    }

    if (action_id == "c67a7830-69cb-452b-839c-62bab571d463") {
        album* tmp = new album(action_id);
        aa = tmp;
        return aa;
    }

    if (action_id == "883b5458-de32-487b-958c-91b0930d4f2c") {
        album* tmp = new album(action_id);
        aa = tmp;
        return aa;
    }

    if (action_id == "ab50be00-33e2-45aa-a887-ac3c2f9cb78c") {
        album* tmp = new album(action_id);
        aa = tmp;
        return aa;
    }

    if (action_id == "b95001cd-7699-4cad-83b4-1d6618d7c3e2") {
        album* tmp = new album(action_id);
        aa = tmp;
        return aa;
    }

    if (action_id == "947dba55-7fb9-4c4e-aa04-5feb7416276f") {
        album* tmp = new album(action_id);
        aa = tmp;
        return aa;
    }

    if (action_id == "721647ab-1d30-4d0a-99dd-649aa27af06e") {
        album* tmp = new album(action_id);
        aa = tmp;
        return aa;
    }

    if (action_id == "cfad3a21-34f5-49cc-9c6a-e5d3c567de8c") {
        album* tmp = new album(action_id);
        aa = tmp;
        return aa;
    }

    if (action_id == "0b4f08da-3c24-4ed5-9e35-d3fa790108ce") {
        album* tmp = new album(action_id);
        aa = tmp;
        return aa;
    }

    if (action_id == "217dab54-7028-4429-bf74-e2e9a7209362") {
        album* tmp = new album(action_id);
        aa = tmp;
        return aa;
    }

    return aa;
}

bool initActionInstance(Action* action) {
    if (action->getElementID() == "17514f4f-ea32-4867-aa04-18f23887b55b") {
        album* tmp = static_cast<album*>(action);
        tmp->is_animating_ = false;
        tmp->left_key_pressed_ = false;
        tmp->right_key_pressed_ = false;
        return true;
    }
    if (action->getElementID() == "c67a7830-69cb-452b-839c-62bab571d463") {
        album* tmp = static_cast<album*>(action);
        tmp->is_animating_ = false;
        tmp->left_key_pressed_ = false;
        tmp->right_key_pressed_ = false;
        return true;
    }
    if (action->getElementID() == "883b5458-de32-487b-958c-91b0930d4f2c") {
        album* tmp = static_cast<album*>(action);
        tmp->is_animating_ = false;
        tmp->left_key_pressed_ = false;
        tmp->right_key_pressed_ = false;
        return true;
    }
    if (action->getElementID() == "ab50be00-33e2-45aa-a887-ac3c2f9cb78c") {
        album* tmp = static_cast<album*>(action);
        tmp->is_animating_ = false;
        tmp->left_key_pressed_ = false;
        tmp->right_key_pressed_ = false;
        return true;
    }
    if (action->getElementID() == "b95001cd-7699-4cad-83b4-1d6618d7c3e2") {
        album* tmp = static_cast<album*>(action);
        tmp->is_animating_ = false;
        tmp->left_key_pressed_ = false;
        tmp->right_key_pressed_ = false;
        return true;
    }
    if (action->getElementID() == "947dba55-7fb9-4c4e-aa04-5feb7416276f") {
        album* tmp = static_cast<album*>(action);
        tmp->is_animating_ = false;
        tmp->left_key_pressed_ = false;
        tmp->right_key_pressed_ = false;
        return true;
    }
    if (action->getElementID() == "721647ab-1d30-4d0a-99dd-649aa27af06e") {
        album* tmp = static_cast<album*>(action);
        tmp->is_animating_ = false;
        tmp->left_key_pressed_ = false;
        tmp->right_key_pressed_ = false;
        return true;
    }
    if (action->getElementID() == "cfad3a21-34f5-49cc-9c6a-e5d3c567de8c") {
        album* tmp = static_cast<album*>(action);
        tmp->is_animating_ = false;
        tmp->left_key_pressed_ = false;
        tmp->right_key_pressed_ = false;
        return true;
    }
    if (action->getElementID() == "0b4f08da-3c24-4ed5-9e35-d3fa790108ce") {
        album* tmp = static_cast<album*>(action);
        tmp->is_animating_ = false;
        tmp->left_key_pressed_ = false;
        tmp->right_key_pressed_ = false;
        return true;
    }
    if (action->getElementID() == "217dab54-7028-4429-bf74-e2e9a7209362") {
        album* tmp = static_cast<album*>(action);
        tmp->is_animating_ = false;
        tmp->left_key_pressed_ = false;
        tmp->right_key_pressed_ = false;
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

    if (action_id == "77764545-79c6-4abd-8e69-22789f9611a6") {
        album* tmp = new album(action_id);
        aa = tmp;
        return aa;
    }

    if (action_id == "6c66b10d-c462-468b-b091-b68445dfeb56") {
        album* tmp = new album(action_id);
        aa = tmp;
        return aa;
    }

    if (action_id == "ab1353f9-b939-4aa4-8b9f-416176c20d6e") {
        album* tmp = new album(action_id);
        aa = tmp;
        return aa;
    }

    if (action_id == "a1de6b32-1d1a-4ea1-b21e-e24bc6890d3b") {
        album* tmp = new album(action_id);
        aa = tmp;
        return aa;
    }

    if (action_id == "856b6cf5-e50a-49e1-a585-244a25c41764") {
        album* tmp = new album(action_id);
        aa = tmp;
        return aa;
    }

    if (action_id == "727375e9-c087-4eaf-bff1-41271a45437c") {
        album* tmp = new album(action_id);
        aa = tmp;
        return aa;
    }

    if (action_id == "09340c03-5a47-4fc4-96fe-cdae5c5d265d") {
        album* tmp = new album(action_id);
        aa = tmp;
        return aa;
    }

    if (action_id == "310ca42e-9ebe-400d-aad8-de3f5edb49db") {
        album* tmp = new album(action_id);
        aa = tmp;
        return aa;
    }

    if (action_id == "fb34a007-276b-4dab-ba22-e9923c57fa60") {
        album* tmp = new album(action_id);
        aa = tmp;
        return aa;
    }

    if (action_id == "ced8da4a-eefa-476d-bd3f-86f7fe45afa4") {
        album* tmp = new album(action_id);
        aa = tmp;
        return aa;
    }

    return aa;
}

bool initPrefabActionInstance(Action* action) {
    if (action->getElementID() == "77764545-79c6-4abd-8e69-22789f9611a6") {
        album* tmp = static_cast<album*>(action);
        tmp->is_animating_ = false;
        tmp->left_key_pressed_ = false;
        tmp->right_key_pressed_ = false;
        return true;
    }
    if (action->getElementID() == "6c66b10d-c462-468b-b091-b68445dfeb56") {
        album* tmp = static_cast<album*>(action);
        tmp->is_animating_ = false;
        tmp->left_key_pressed_ = false;
        tmp->right_key_pressed_ = false;
        return true;
    }
    if (action->getElementID() == "ab1353f9-b939-4aa4-8b9f-416176c20d6e") {
        album* tmp = static_cast<album*>(action);
        tmp->is_animating_ = false;
        tmp->left_key_pressed_ = false;
        tmp->right_key_pressed_ = false;
        return true;
    }
    if (action->getElementID() == "a1de6b32-1d1a-4ea1-b21e-e24bc6890d3b") {
        album* tmp = static_cast<album*>(action);
        tmp->is_animating_ = false;
        tmp->left_key_pressed_ = false;
        tmp->right_key_pressed_ = false;
        return true;
    }
    if (action->getElementID() == "856b6cf5-e50a-49e1-a585-244a25c41764") {
        album* tmp = static_cast<album*>(action);
        tmp->is_animating_ = false;
        tmp->left_key_pressed_ = false;
        tmp->right_key_pressed_ = false;
        return true;
    }
    if (action->getElementID() == "727375e9-c087-4eaf-bff1-41271a45437c") {
        album* tmp = static_cast<album*>(action);
        tmp->is_animating_ = false;
        tmp->left_key_pressed_ = false;
        tmp->right_key_pressed_ = false;
        return true;
    }
    if (action->getElementID() == "09340c03-5a47-4fc4-96fe-cdae5c5d265d") {
        album* tmp = static_cast<album*>(action);
        tmp->is_animating_ = false;
        tmp->left_key_pressed_ = false;
        tmp->right_key_pressed_ = false;
        return true;
    }
    if (action->getElementID() == "310ca42e-9ebe-400d-aad8-de3f5edb49db") {
        album* tmp = static_cast<album*>(action);
        tmp->is_animating_ = false;
        tmp->left_key_pressed_ = false;
        tmp->right_key_pressed_ = false;
        return true;
    }
    if (action->getElementID() == "fb34a007-276b-4dab-ba22-e9923c57fa60") {
        album* tmp = static_cast<album*>(action);
        tmp->is_animating_ = false;
        tmp->left_key_pressed_ = false;
        tmp->right_key_pressed_ = false;
        return true;
    }
    if (action->getElementID() == "ced8da4a-eefa-476d-bd3f-86f7fe45afa4") {
        album* tmp = static_cast<album*>(action);
        tmp->is_animating_ = false;
        tmp->left_key_pressed_ = false;
        tmp->right_key_pressed_ = false;
        return true;
    }
    else {
        std::cerr << "Error: Unknown prefab action ID: " << action->getElementID() << std::endl;
        return false;
    }
    return true;
}

}  // namespace grapi::runtime
