#include <iostream>

#include "grapi/runtime/display_object.h"
#include "grapi/runtime/transform.h"
#include "speed_needle_pivot.h"

speed_needle_pivot::speed_needle_pivot(const grapi::base::String& id, const grapi::base::TypeInfo* type_info) : grapi::runtime::Action(id, type_info) {
}

speed_needle_pivot::~speed_needle_pivot() {
}

void speed_needle_pivot::start() {
    // Scene 에 추가될 때 한번만 실행된다.
    pivot = this->getParent();
    if (!pivot) return;
    transform = pivot->getTransform();
}

void speed_needle_pivot::update(const vfloat delta_time) {
    if (!pivot) return;

    const vfloat speed = (kMaxZ - kMinZ) / kDuration;
    current_z_ += direction_ * speed * delta_time;

    if (current_z_ >= kMaxZ) {
        current_z_ = kMaxZ;  // 최대값(-0.0f)에 도달하면 아래로 내려감
        direction_ = -1.0f;
    } else if (current_z_ <= kMinZ) {
        current_z_ = kMinZ;  // 최소값(-233.0f)에 도달하면 위로 올라감
        direction_ = 1.0f;
    }

    
    if (transform) {
        vfloat x = transform->getRotation().x;
        vfloat y = transform->getRotation().y;
        transform->setRotation(glm::vec3(x, y, current_z_));
    }
}