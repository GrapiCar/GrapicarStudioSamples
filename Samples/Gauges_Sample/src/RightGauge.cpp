#include <cmath>
#include "grapi/runtime/display_object.h"
#include "grapi/runtime/transform.h"
#include "grapi/runtime/utils.h"
#include "RightGauge.h"
#include <iostream>

namespace {
    /** Y 이동 범위: currentY ~ currentY + 400 */
    constexpr vfloat kRpmYRange = 400.f;
    float s_rpmNormalized = 0.5f;
}

float RightGauge::getRpmNormalized() {
    return s_rpmNormalized;
}

RightGauge::RightGauge(const grapi::base::String& id, const grapi::base::TypeInfo* type_info) : grapi::runtime::Action(id, type_info) {
}

RightGauge::~RightGauge() {
}

void RightGauge::start() {
    setupRightGauge();
}

void RightGauge::update(const vfloat delta_time) {
    updateRightGauge(delta_time);
}

void RightGauge::setupRightGauge() {
    right = this->getParent();
    
    if(!right) {
        std::cout << "RightGauge::setupRightGauge() : right is not found" << std::endl;
    }
    if (right && right->getTransform()) {
        baseY_ = right->getTransform()->getPosition().y;
    }
}

void RightGauge::updateRightGauge(const vfloat delta_time) {
    // 매 프레임 시간 누적 → RPM 값 계속 갱신 (끊김 없이 계속 움직임)
    simTime_ += delta_time;
    s_rpmNormalized = 0.5f + 0.45f * std::sin(simTime_ * 0.8f);
    if (s_rpmNormalized < 0.f) s_rpmNormalized = 0.f;
    if (s_rpmNormalized > 1.f) s_rpmNormalized = 1.f;

    if (!right || !right->getTransform()) return;
    glm::vec3 pos = right->getTransform()->getPosition();
    vfloat y = baseY_ + kRpmYRange * s_rpmNormalized;  // 현재위치 ~ +400
    right->getTransform()->setPosition(glm::vec3(pos.x, y, pos.z));
}