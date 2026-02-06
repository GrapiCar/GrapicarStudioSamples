#ifndef _ALBUM_H_
#define _ALBUM_H_

#include "grapi/runtime/action.h"
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

class album : public grapi::runtime::Action 
{
public:
    SET_ACTION_INSTANCE(album);

    album(const grapi::base::String& id, const grapi::base::TypeInfo* type_info = &kTypeInfo);
    virtual ~album();

    virtual void start() override;
    virtual void update(const vfloat delta_time) override;

    void setup();

    // 5개의 앨범 객체
    grapi::runtime::DisplayObject* album1_ = nullptr;
    grapi::runtime::DisplayObject* album2_ = nullptr;
    grapi::runtime::DisplayObject* album3_ = nullptr;
    grapi::runtime::DisplayObject* album4_ = nullptr;
    grapi::runtime::DisplayObject* album5_ = nullptr;

    // 5개의 반사 앨범 객체
    grapi::runtime::DisplayObject* reflectedAlbum1_ = nullptr;
    grapi::runtime::DisplayObject* reflectedAlbum2_ = nullptr;
    grapi::runtime::DisplayObject* reflectedAlbum3_ = nullptr;
    grapi::runtime::DisplayObject* reflectedAlbum4_ = nullptr;
    grapi::runtime::DisplayObject* reflectedAlbum5_ = nullptr;

    // 각 앨범의 위치 (5개 위치)
    glm::vec3 positions_[5] = {
        glm::vec3(0.0f, 0.0f, 0.0f),      // 0: 맨 앞
        glm::vec3(3.0f, 0.0f, -3.0f),     // 1: 오른쪽 뒤 앞
        glm::vec3(5.0f, 0.0f, -4.0f),     // 2: 오른쪽 맨 뒤
        glm::vec3(-5.0f, 0.0f, -4.0f),   // 3: 왼쪽 맨 뒤
        glm::vec3(-3.0f, 0.0f, -3.0f)     // 4: 왼쪽 뒤 앞
    };

    // 각 위치에 따른 회전
    glm::vec3 rotations_[5] = {
        glm::vec3(0.0f, 0.0f, 0.0f),      // 0: 맨 앞
        glm::vec3(0.0f, -35.0f, 0.0f),   // 1: 오른쪽 뒤 앞
        glm::vec3(0.0f, -35.0f, 0.0f),   // 2: 오른쪽 맨 뒤
        glm::vec3(0.0f, 35.0f, 0.0f),    // 3: 왼쪽 맨 뒤
        glm::vec3(0.0f, 35.0f, 0.0f)     // 4: 왼쪽 뒤 앞
    };

    // 현재 각 앨범이 어떤 위치에 있는지 인덱스
    int album1_position_index_ = 0;  // 맨 앞
    int album2_position_index_ = 1;  // 오른쪽 뒤 앞
    int album3_position_index_ = 2;  // 오른쪽 맨 뒤
    int album4_position_index_ = 3;  // 왼쪽 맨 뒤
    int album5_position_index_ = 4;  // 왼쪽 뒤 앞

    // 각 앨범의 현재 위치와 회전 (애니메이션용)
    glm::vec3 album1_current_pos_ = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 album2_current_pos_ = glm::vec3(3.0f, 0.0f, -3.0f);
    glm::vec3 album3_current_pos_ = glm::vec3(5.0f, 0.0f, -4.0f);
    glm::vec3 album4_current_pos_ = glm::vec3(-5.0f, 0.0f, -4.0f);
    glm::vec3 album5_current_pos_ = glm::vec3(-3.0f, 0.0f, -3.0f);
    glm::vec3 album1_current_rot_ = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 album2_current_rot_ = glm::vec3(0.0f, -35.0f, 0.0f);
    glm::vec3 album3_current_rot_ = glm::vec3(0.0f, -35.0f, 0.0f);
    glm::vec3 album4_current_rot_ = glm::vec3(0.0f, 35.0f, 0.0f);
    glm::vec3 album5_current_rot_ = glm::vec3(0.0f, 35.0f, 0.0f);

    // 애니메이션 관련 변수
    float animation_time_ = 0.0f;
    float animation_duration_ = 0.5f;  // 0.5초 동안 이동
    bool is_animating_ = false;

    // 배경색 관련 변수 (초기화만 하고 변경하지 않음)
    glm::vec4 bg_color_ = glm::vec4(0.02f, 0.02f, 0.02f, 1.0f);  // 어두운 회색

    // 키 입력 상태 추적 (중복 입력 방지)
    bool left_key_pressed_ = false;
    bool right_key_pressed_ = false;

    // 위치를 순환시키는 함수
    void rotateLeft();
    void rotateRight();

    // 배경색 업데이트 함수
    void updateBackgroundColor();
};

#endif