#include <iostream>

#include "grapi/runtime/display_object.h"
#include "grapi/runtime/transform.h"
#include "fuel.h"

fuel::fuel(const grapi::base::String& id, const grapi::base::TypeInfo* type_info) : grapi::runtime::Action(id, type_info) {
}

fuel::~fuel() {
}

void fuel::start() {
    gauge = this->getParent();
    transform = gauge->getTransform();
    // gauge->getTransform()->setPosition(glm::vec3(0.0f, -592.0f, 0.0f));
}

void fuel::update(const vfloat delta_time) {
    if (!gauge) return;

    const vfloat speed = (kMaxY - kMinY) / kDuration;
    current_y_ += direction_ * speed * delta_time;

    if (current_y_ >= kMaxY) {
        current_y_ = kMaxY;   // 0에 닿으면 -592로 내려감
        direction_ = -1.0f;
    } else if (current_y_ <= kMinY) {
        current_y_ = kMinY;   // -592에 닿으면 0으로 올라감
        direction_ = 1.0f;
    }

    
    if (transform) {
        vfloat x = t->getPosition().x;
        t->setPosition(glm::vec3(x, current_y_, 0.0f));
    }
}