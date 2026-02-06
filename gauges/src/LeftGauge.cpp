#include "grapi/runtime/display_object.h"
#include "grapi/runtime/transform.h"
#include "grapi/runtime/utils.h"
#include "LeftGauge.h"
#include "RightGauge.h"
#include <iostream>

namespace {
    /** Y 이동 범위: currentY ~ currentY + 400 */
    constexpr vfloat kSpeedYRange = 400.f;
    constexpr vfloat kSpeedFollowRate = 2.5f;
    constexpr vfloat kSpeedDecayRate = 0.8f;
}

LeftGauge::LeftGauge(const grapi::base::String& id, const grapi::base::TypeInfo* type_info) : grapi::runtime::Action(id, type_info) {
}

LeftGauge::~LeftGauge() {
}

void LeftGauge::start() {
    setupLeftGauge();
}

void LeftGauge::update(const vfloat delta_time) {
    updateLeftGauge(delta_time);
}

void LeftGauge::setupLeftGauge() {
    left = this->getParent();
 
    if(!left) {
        std::cout << "LeftGauge::setupLeftGauge() : left is not found" << std::endl;
    }
    if (left && left->getTransform()) {
        baseY_ = left->getTransform()->getPosition().y;
    }
}

void LeftGauge::updateLeftGauge(const vfloat delta_time) {
    if (!left || !left->getTransform()) return;

    float rpm = RightGauge::getRpmNormalized();
    // 가속: RPM이 올라가면 목표는 RPM까지 (속도는 천천히 따라감)
    if (rpm > speedTarget_) {
        speedTarget_ = rpm;
    } else {
        // 감속: RPM보다 속도가 높을 수 있음(오버드라이브). 목표는 천천히 RPM 쪽으로
        speedTarget_ += (rpm - speedTarget_) * kSpeedDecayRate * delta_time;
    }
    if (speedTarget_ < 0.f) speedTarget_ = 0.f;
    if (speedTarget_ > 1.f) speedTarget_ = 1.f;

    currentSpeed_ += (speedTarget_ - currentSpeed_) * kSpeedFollowRate * delta_time;
    if (currentSpeed_ < 0.f) currentSpeed_ = 0.f;
    if (currentSpeed_ > 1.f) currentSpeed_ = 1.f;

    glm::vec3 pos = left->getTransform()->getPosition();
    vfloat y = baseY_ + kSpeedYRange * currentSpeed_;  // 현재위치 ~ +400
    left->getTransform()->setPosition(glm::vec3(pos.x, y, pos.z));
}