#include <iostream>

#include "grapi/runtime/display_object.h"
#include "grapi/runtime/transform.h"
#include "AnimatorStateMachine.h"
#include "grapi/runtime/animator.h"

#include <windows.h>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <cmath>


AnimatorStateMachine::AnimatorStateMachine(const grapi::base::String& id, const grapi::base::TypeInfo* type_info) : grapi::runtime::Action(id, type_info) {
}

AnimatorStateMachine::~AnimatorStateMachine() {
}

void AnimatorStateMachine::start() {
    // Scene 에 추가될 때 한번만 실행된다.
    grapi::runtime::DisplayObject* object = this->getParent();
    
    if(!object) {
        std::cerr << "AnimatorStateMachine: Parent object not found" << std::endl;
        return;
    }

    animator->play("Entry");

    //animator = object->getComponent<grapi::runtime::Animator>();
    isMusic = animator->getBoolPtr("isMusic");
    isNAv = animator->getBoolPtr("isNav");
    if(!animator) {
        std::cerr << "AnimatorStateMachine: Animator component not found" << std::endl;
        return;
    }
}

void AnimatorStateMachine::update(const vfloat delta_time) {
    // Update 로직을 여기에 구현하세요
    handleKeyPress();
    // setupUpdate(delta_time);
}

void AnimatorStateMachine::handleKeyPress() {
    static bool prev_m = false;
    
    bool curr_m = (GetAsyncKeyState('M') & 0x8000) != 0;

    if(curr_m && !prev_m) {
        int nextMode = state + 1;
        if(nextMode > 1) {
            nextMode = 0;
        }

        *isMusic = (state == 0);
        *isNAv = (state == 1);

        state = nextMode;
        // setupUpdate(state);
        std::cout << "State: " << state << std::endl;
    }    
    prev_m = curr_m;
}

void AnimatorStateMachine::setupUpdate(const int state) {
    // switch(state) {
    //     case 0:
    //     animator->setBool("isNAv", false);
    //     animator->setBool("isMusic", true);
    //     animator->getClipByName("music")->setClampWhenFinished(true);
    //     animator->play("music");
    //         break;
    //     case 1:
    //     animator->setBool("isNAv", true);
    //     animator->setBool("isMusic", false);
    //     animator->getClipByName("nav")->setClampWhenFinished(true);
    //     animator->play("nav");
    //         break;
    // }
}