#include <iostream>

#include "grapi/runtime/display_object.h"
#include "grapi/runtime/transform.h"
#include "speed_number.h"

speed_number::speed_number(const grapi::base::String& id, const grapi::base::TypeInfo* type_info) : grapi::runtime::Action(id, type_info) {
}

speed_number::~speed_number() {
}

void speed_number::start() {
    // Scene 에 추가될 때 한번만 실행된다.
    number = this->getParent();
    if (!number) return;
    transform = number->getTransform();

    // 초기 position x 저장
    if (transform) {
        initial_position_x_ = transform->getPosition().x;
        std::cout << "Initial position x: " << initial_position_x_ << std::endl;
    }

    // child 객체들 가져오기
    auto& children = number->getChildObjects();
    if (children.size() >= 3) {
        for (int i = 0; i < 10; i++) {
            auto& hundred_children = children[0]->getChildObjects();
            auto& ten_children = children[1]->getChildObjects();
            auto& one_children = children[2]->getChildObjects();
            
            if (hundred_children.size() > i) hundred[i] = hundred_children[i];
            if (ten_children.size() > i) ten[i] = ten_children[i];
            if (one_children.size() > i) one[i] = one_children[i];
        }
    }
}

void speed_number::update(const vfloat delta_time) {
    if (!number) return;

    updateVelocity(delta_time);
    int velocity = static_cast<int>(velocity_);
    updatePosition(velocity);
    updateNumberDisplay(velocity);
}

void speed_number::updateVelocity(const vfloat delta_time) {
    // velocity를 독자적으로 증가/감소시킴
    const vfloat speed = static_cast<vfloat>(kMaxVelocity) / kDuration;
    velocity_ += direction_ * speed * delta_time;

    // velocity 범위 제한 및 방향 전환
    if (velocity_ >= static_cast<vfloat>(kMaxVelocity)) {
        velocity_ = static_cast<vfloat>(kMaxVelocity);
        direction_ = -1.0f;
    } else if (velocity_ <= 0.0f) {
        velocity_ = 0.0f;
        direction_ = 1.0f;
    }
}

void speed_number::updatePosition(int velocity) {
    if (!transform) {
        std::cout << "Warning: transform is null!" << std::endl;
        return;
    }
    
    bool should_adjust = (velocity >= 100);
    if (should_adjust && !position_adjusted_) {
        // 100 이상이 되면 x를 12만큼 이동
        vfloat current_x = transform->getPosition().x;
        vfloat current_y = transform->getPosition().y;
        vfloat current_z_pos = transform->getPosition().z;
        vfloat new_x = initial_position_x_ + kPositionOffsetX;
        transform->setPosition(glm::vec3(new_x, current_y, current_z_pos));
        position_adjusted_ = true;
        std::cout << "Position adjusted: " << current_x << " -> " << new_x << " (velocity: " << velocity << ")" << std::endl;
    } else if (!should_adjust && position_adjusted_) {
        // 100 미만으로 내려가면 원래 위치로 복귀
        vfloat current_y = transform->getPosition().y;
        vfloat current_z_pos = transform->getPosition().z;
        transform->setPosition(glm::vec3(initial_position_x_, current_y, current_z_pos));
        position_adjusted_ = false;
        std::cout << "Position reset to: " << initial_position_x_ << " (velocity: " << velocity << ")" << std::endl;
    }
}

void speed_number::updateNumberDisplay(int velocity) {
    // 각 자리수 추출
    int hundred_digit = velocity / 100;
    int ten_digit = (velocity / 10) % 10;
    int one_digit = velocity % 10;

    // 모든 숫자 숨기기
    for (int i = 0; i < 10; i++) {
        if (hundred[i]) hundred[i]->setVisible(false);
        if (ten[i]) ten[i]->setVisible(false);
        if (one[i]) one[i]->setVisible(false);
    }

    // hundred 자리수 표시 (100 이상일 때만)
    if (velocity >= 100 && hundred[hundred_digit]) {
        hundred[hundred_digit]->setVisible(true);
    }

    // ten 자리수 표시 (항상 표시)
    if (ten[ten_digit]) {
        ten[ten_digit]->setVisible(true);
    }

    // one 자리수 표시 (항상 표시)
    if (one[one_digit]) {
        one[one_digit]->setVisible(true);
    }
    
    // 디버깅용 출력 (필요시 주석 해제)
    // std::cout << "velocity: " << velocity << " (hundred: " << hundred_digit << ", ten: " << ten_digit << ", one: " << one_digit << ")" << std::endl;
}