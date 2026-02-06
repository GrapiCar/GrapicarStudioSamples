#include <iostream>
#include <windows.h>

#include "grapi/runtime/display_object.h"
#include "grapi/runtime/transform.h"
#include "grapi/runtime/utils.h"
#include "grapi/runtime/scene.h"
#include "grapi/base/object.h"
#include "album.h"
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/common.hpp>
#include <cmath>

album::album(const grapi::base::String& id, const grapi::base::TypeInfo* type_info) : grapi::runtime::Action(id, type_info) {
}

album::~album() {
}

void album::start() {
    // Scene 에 추가될 때 한번만 실행된다.
    setup();
}

void album::update(const vfloat delta_time) {
    // Windows API를 사용하여 방향키 입력 감지
    SHORT left_key_state = GetAsyncKeyState(VK_LEFT);
    SHORT right_key_state = GetAsyncKeyState(VK_RIGHT);
    
    bool left_key_current = (left_key_state & 0x8000) != 0;
    bool right_key_current = (right_key_state & 0x8000) != 0;

    // 키가 눌렸다가 떼어졌을 때만 동작 (중복 입력 방지)
    if (left_key_current && !left_key_pressed_ && !is_animating_) {
        rotateLeft();
        left_key_pressed_ = true;
    } else if (!left_key_current) {
        left_key_pressed_ = false;
    }

    if (right_key_current && !right_key_pressed_ && !is_animating_) {
        rotateRight();
        right_key_pressed_ = true;
    } else if (!right_key_current) {
        right_key_pressed_ = false;
    }

    // 애니메이션 업데이트
    if (is_animating_) {
        animation_time_ += delta_time;
        
        if (animation_time_ >= animation_duration_) {
            // 애니메이션 완료
            animation_time_ = animation_duration_;
            is_animating_ = false;
            album1_current_pos_ = positions_[album1_position_index_];
            album2_current_pos_ = positions_[album2_position_index_];
            album3_current_pos_ = positions_[album3_position_index_];
            album4_current_pos_ = positions_[album4_position_index_];
            album5_current_pos_ = positions_[album5_position_index_];
            album1_current_rot_ = rotations_[album1_position_index_];
            album2_current_rot_ = rotations_[album2_position_index_];
            album3_current_rot_ = rotations_[album3_position_index_];
            album4_current_rot_ = rotations_[album4_position_index_];
            album5_current_rot_ = rotations_[album5_position_index_];
        }
        
        // 진행도 계산 (0~1 사이 값)
        float progress = animation_time_ / animation_duration_;
        
        // 부드러운 이징 함수 (ease-in-out)
        float eased_progress = progress < 0.5f ? 
            2.0f * progress * progress : 
            -1.0f + (4.0f - 2.0f * progress) * progress;
        
        // 현재 위치를 목표 위치로 보간
        album1_current_pos_ = glm::mix(album1_current_pos_, positions_[album1_position_index_], eased_progress);
        album2_current_pos_ = glm::mix(album2_current_pos_, positions_[album2_position_index_], eased_progress);
        album3_current_pos_ = glm::mix(album3_current_pos_, positions_[album3_position_index_], eased_progress);
        album4_current_pos_ = glm::mix(album4_current_pos_, positions_[album4_position_index_], eased_progress);
        album5_current_pos_ = glm::mix(album5_current_pos_, positions_[album5_position_index_], eased_progress);

        // 현재 회전을 목표 회전으로 보간
        album1_current_rot_ = glm::mix(album1_current_rot_, rotations_[album1_position_index_], eased_progress);
        album2_current_rot_ = glm::mix(album2_current_rot_, rotations_[album2_position_index_], eased_progress);
        album3_current_rot_ = glm::mix(album3_current_rot_, rotations_[album3_position_index_], eased_progress);
        album4_current_rot_ = glm::mix(album4_current_rot_, rotations_[album4_position_index_], eased_progress);
        album5_current_rot_ = glm::mix(album5_current_rot_, rotations_[album5_position_index_], eased_progress);
    }

    // 매 프레임마다 위치와 회전 업데이트
    if (album1_ && album1_->getTransform()) {
        album1_->getTransform()->setPosition(album1_current_pos_);
        album1_->getTransform()->setRotation(album1_current_rot_);
    }
    if (album2_ && album2_->getTransform()) {
        album2_->getTransform()->setPosition(album2_current_pos_);
        album2_->getTransform()->setRotation(album2_current_rot_);
    }
    if (album3_ && album3_->getTransform()) {
        album3_->getTransform()->setPosition(album3_current_pos_);
        album3_->getTransform()->setRotation(album3_current_rot_);
    }
    if (album4_ && album4_->getTransform()) {
        album4_->getTransform()->setPosition(album4_current_pos_);
        album4_->getTransform()->setRotation(album4_current_rot_);
    }
    if (album5_ && album5_->getTransform()) {
        album5_->getTransform()->setPosition(album5_current_pos_);
        album5_->getTransform()->setRotation(album5_current_rot_);
    }

    // 반사 앨범 위치와 회전 업데이트 (Y축으로 -3.5 이동)
    if (reflectedAlbum1_ && reflectedAlbum1_->getTransform()) {
        glm::vec3 reflected_pos = album1_current_pos_;
        reflected_pos.y -= 3.5f;
        reflectedAlbum1_->getTransform()->setPosition(reflected_pos);
        reflectedAlbum1_->getTransform()->setRotation(album1_current_rot_);
    }
    if (reflectedAlbum2_ && reflectedAlbum2_->getTransform()) {
        glm::vec3 reflected_pos = album2_current_pos_;
        reflected_pos.y -= 3.5f;
        reflectedAlbum2_->getTransform()->setPosition(reflected_pos);
        reflectedAlbum2_->getTransform()->setRotation(album2_current_rot_);
    }
    if (reflectedAlbum3_ && reflectedAlbum3_->getTransform()) {
        glm::vec3 reflected_pos = album3_current_pos_;
        reflected_pos.y -= 3.5f;
        reflectedAlbum3_->getTransform()->setPosition(reflected_pos);
        reflectedAlbum3_->getTransform()->setRotation(album3_current_rot_);
    }
    if (reflectedAlbum4_ && reflectedAlbum4_->getTransform()) {
        glm::vec3 reflected_pos = album4_current_pos_;
        reflected_pos.y -= 3.5f;
        reflectedAlbum4_->getTransform()->setPosition(reflected_pos);
        reflectedAlbum4_->getTransform()->setRotation(album4_current_rot_);
    }
    if (reflectedAlbum5_ && reflectedAlbum5_->getTransform()) {
        glm::vec3 reflected_pos = album5_current_pos_;
        reflected_pos.y -= 3.5f;
        reflectedAlbum5_->getTransform()->setPosition(reflected_pos);
        reflectedAlbum5_->getTransform()->setRotation(album5_current_rot_);
    }
}

void album::setup() {
    // 5개의 앨범 객체 찾기
    album1_ = grapi::runtime::findObjectByName("album1");
    album2_ = grapi::runtime::findObjectByName("album2");
    album3_ = grapi::runtime::findObjectByName("album3");
    album4_ = grapi::runtime::findObjectByName("album4");
    album5_ = grapi::runtime::findObjectByName("album5");

    // 5개의 반사 앨범 객체 찾기
    reflectedAlbum1_ = grapi::runtime::findObjectByName("reflectedAlbum1");
    reflectedAlbum2_ = grapi::runtime::findObjectByName("reflectedAlbum2");
    reflectedAlbum3_ = grapi::runtime::findObjectByName("reflectedAlbum3");
    reflectedAlbum4_ = grapi::runtime::findObjectByName("reflectedAlbum4");
    reflectedAlbum5_ = grapi::runtime::findObjectByName("reflectedAlbum5");

    // 초기 위치 및 회전 설정
    album1_current_pos_ = positions_[album1_position_index_];
    album2_current_pos_ = positions_[album2_position_index_];
    album3_current_pos_ = positions_[album3_position_index_];
    album4_current_pos_ = positions_[album4_position_index_];
    album5_current_pos_ = positions_[album5_position_index_];
    album1_current_rot_ = rotations_[album1_position_index_];
    album2_current_rot_ = rotations_[album2_position_index_];
    album3_current_rot_ = rotations_[album3_position_index_];
    album4_current_rot_ = rotations_[album4_position_index_];
    album5_current_rot_ = rotations_[album5_position_index_];

    if (album1_ && album1_->getTransform()) {
        album1_->getTransform()->setPosition(album1_current_pos_);
        album1_->getTransform()->setRotation(album1_current_rot_);
    }
    if (album2_ && album2_->getTransform()) {
        album2_->getTransform()->setPosition(album2_current_pos_);
        album2_->getTransform()->setRotation(album2_current_rot_);
    }
    if (album3_ && album3_->getTransform()) {
        album3_->getTransform()->setPosition(album3_current_pos_);
        album3_->getTransform()->setRotation(album3_current_rot_);
    }
    if (album4_ && album4_->getTransform()) {
        album4_->getTransform()->setPosition(album4_current_pos_);
        album4_->getTransform()->setRotation(album4_current_rot_);
    }
    if (album5_ && album5_->getTransform()) {
        album5_->getTransform()->setPosition(album5_current_pos_);
        album5_->getTransform()->setRotation(album5_current_rot_);
    }

    // 반사 앨범 초기 위치 및 회전 설정 (Y축으로 -3.5 이동)
    if (reflectedAlbum1_ && reflectedAlbum1_->getTransform()) {
        glm::vec3 reflected_pos = album1_current_pos_;
        reflected_pos.y -= 3.5f;
        reflectedAlbum1_->getTransform()->setPosition(reflected_pos);
        reflectedAlbum1_->getTransform()->setRotation(album1_current_rot_);
    }
    if (reflectedAlbum2_ && reflectedAlbum2_->getTransform()) {
        glm::vec3 reflected_pos = album2_current_pos_;
        reflected_pos.y -= 3.5f;
        reflectedAlbum2_->getTransform()->setPosition(reflected_pos);
        reflectedAlbum2_->getTransform()->setRotation(album2_current_rot_);
    }
    if (reflectedAlbum3_ && reflectedAlbum3_->getTransform()) {
        glm::vec3 reflected_pos = album3_current_pos_;
        reflected_pos.y -= 3.5f;
        reflectedAlbum3_->getTransform()->setPosition(reflected_pos);
        reflectedAlbum3_->getTransform()->setRotation(album3_current_rot_);
    }
    if (reflectedAlbum4_ && reflectedAlbum4_->getTransform()) {
        glm::vec3 reflected_pos = album4_current_pos_;
        reflected_pos.y -= 3.5f;
        reflectedAlbum4_->getTransform()->setPosition(reflected_pos);
        reflectedAlbum4_->getTransform()->setRotation(album4_current_rot_);
    }
    if (reflectedAlbum5_ && reflectedAlbum5_->getTransform()) {
        glm::vec3 reflected_pos = album5_current_pos_;
        reflected_pos.y -= 3.5f;
        reflectedAlbum5_->getTransform()->setPosition(reflected_pos);
        reflectedAlbum5_->getTransform()->setRotation(album5_current_rot_);
    }

    // 초기 배경색 설정 (한 번만 설정하고 변경하지 않음)
    updateBackgroundColor();
}

void album::rotateLeft() {
    // 왼쪽 방향키: 위치를 왼쪽으로 순환
    // 맨 앞(0) → 오른쪽 뒤 앞(1) → 오른쪽 맨 뒤(2) → 왼쪽 맨 뒤(3) → 왼쪽 뒤 앞(4) → 맨 앞(0)
    int temp = album1_position_index_;
    album1_position_index_ = album2_position_index_;
    album2_position_index_ = album3_position_index_;
    album3_position_index_ = album4_position_index_;
    album4_position_index_ = album5_position_index_;
    album5_position_index_ = temp;

    // 애니메이션 시작
    animation_time_ = 0.0f;
    is_animating_ = true;
}

void album::rotateRight() {
    // 오른쪽 방향키: 위치를 오른쪽으로 순환
    // 맨 앞(0) → 왼쪽 뒤 앞(4) → 왼쪽 맨 뒤(3) → 오른쪽 맨 뒤(2) → 오른쪽 뒤 앞(1) → 맨 앞(0)
    int temp = album1_position_index_;
    album1_position_index_ = album5_position_index_;
    album5_position_index_ = album4_position_index_;
    album4_position_index_ = album3_position_index_;
    album3_position_index_ = album2_position_index_;
    album2_position_index_ = temp;

    // 애니메이션 시작
    animation_time_ = 0.0f;
    is_animating_ = true;
}

void album::updateBackgroundColor() {
    // Scene에 접근하여 초기 색상만 설정 (변경하지 않음)
    grapi::runtime::DisplayObject* root = this->getParent();
    if (root) {
        root = root->getRootParent();
    }
    
    if (root) {
        // DisplayObject를 Scene으로 캐스팅
        grapi::runtime::Scene* scene = dynamic_cast<grapi::runtime::Scene*>(root);
        if (scene) {
            // 초기 색상으로 설정 (변경하지 않음)
            scene->setBackgroundColor(bg_color_);
        }
    }
}