#include <iostream>

#include "grapi/runtime/display_object.h"
#include "grapi/runtime/transform.h"
#include "AnimationWithChild.h"
#include "grapi/runtime/animator.h"
#include "grapi/runtime/animation_clip.h"
#include "grapi/runtime/utils.h"

AnimationWithChild::AnimationWithChild(const grapi::base::String& id, const grapi::base::TypeInfo* type_info) : grapi::runtime::Action(id, type_info) {
}

AnimationWithChild::~AnimationWithChild() {
}

void AnimationWithChild::start() {
    // Scene 에 추가될 때 한번만 실행된다.
    setupAnimation();
}

void AnimationWithChild::update(const vfloat delta_time) {
    // Update 로직을 여기에 구현하세요
    updateAnimation(delta_time);
}

void AnimationWithChild::setupAnimation()
{
    // 부모 객체의 자식 객체들을 가져온다
    grapi::runtime::DisplayObject* target = grapi::runtime::findObjectByName("Object04");

    if(!target) {
        std::cout << "[AnimationWithChild.cpp] Object04 not found in the scene." << std::endl;
        return;
    }

    grapi::runtime::Animator* animator = target->getComponent<grapi::runtime::Animator>();

    if (!animator) {
        std::cout << "[AnimationWithChild.cpp] Animator component not found on Object04." << std::endl;
        return;
    }

    std::cout << "[AnimationWithChild.cpp] Setting up animation for Object04." << std::endl;
    
    animator->play("withChild");
}

void AnimationWithChild::updateAnimation(const vfloat delta_time)
{
    // Animation 업데이트 로직을 여기에 구현하세요
    // delta_time을 사용하여 애니메이션 진행 상황 추적
}