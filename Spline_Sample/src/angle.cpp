#include <iostream>

#include "grapi/runtime/display_object.h"
#include "grapi/runtime/transform.h"
#include "grapi/runtime/arc.h"
#include "grapi/runtime/utils.h"
#include "angle.h"

angle::angle(const grapi::base::String& id, const grapi::base::TypeInfo* type_info) : grapi::runtime::Action(id, type_info) {
}

angle::~angle() {
}

void angle::start() {
    // Scene 에 추가될 때 한번만 실행된다.
    setupArc();
}

void angle::update(const vfloat delta_time) {
    // Update 로직을 여기에 구현하세요
    updateArc(delta_time);
}

void angle::setupArc() {
    // Arc 설정 로직을 여기에 구현하세요
    grapi::runtime::DisplayObject* target = grapi::runtime::findObjectByName("AngleArc");

    if(!target) {
        std::cout << "Not Found AngleArc" << std::endl;
        return;
    }

    grapi::runtime::Arc* arc = target->getComponent<grapi::runtime::Arc>();
    if(!arc) {
        std::cout << "Not Found Arc Component" << std::endl;
        return;
    }

    arc_ = arc;
}

void angle::updateArc(const vfloat delta_time) {
    // Arc 업데이트 로직을 여기에 구현하세요
    if(!arc_) return;
}