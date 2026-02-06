#include <iostream>

#include "grapi/runtime/display_object.h"
#include "grapi/runtime/transform.h"
#include "grapi/runtime/cell_image_mixer.h"
#include "grapi/runtime/utils.h"
#include "cell01.h"
#include "grapi/runtime/input_state.h"

using namespace grapi::runtime;
using namespace grapi::base;

cell01::cell01(const grapi::base::String& id, const grapi::base::TypeInfo* type_info) : grapi::runtime::Action(id, type_info) {
    current_state_ = 0;
}

cell01::~cell01() {
}

void cell01::start() {
    setupCell();  
}

void cell01::update(const vfloat delta_time) {
    updateCell();
}

void cell01::setupCell()
{
    // 부모 객체의 자식들을 순회하여 CellImageMixer 컴포넌트 찾기
    grapi::runtime::DisplayObject* target = grapi::runtime::findObjectByName("DefaultCell");

    if(!target) {
        std::cout << "Cannot find DefaultCell object!" << std::endl;
        return;
    }

    std::cout << "This Object Name: " << this->getParent()->getName() << std::endl;

    grapi::runtime::CellImageMixer* mixer = target->getComponent<grapi::runtime::CellImageMixer>();

    if(!mixer) {
        std::cout << "Cannot find CellImageMixer component!" << std::endl;
        return;
    }

    cell_mixer_ = mixer;

    
    cell_mixer_->play(true);
    
}

void cell01::updateCell()
{
    if (cell_mixer_ == nullptr)
    {
        return;
    }

    // 상태에 따른 CellImageMixer 제어 예제
    // 필요에 따라 조건을 변경하여 사용
    
    // 예제: 특정 조건에 따라 재생/정지
    // if (some_condition)
    // {
    //     if (current_state_ != 1 && !cell_mixer_->isPlaying())
    //     {
    //         current_state_ = 1;
    //         cell_mixer_->play(true);  // 반복 재생
    //     }
    // }
    // else
    // {
    //     if (current_state_ != 0 && cell_mixer_->isPlaying())
    //     {
    //         current_state_ = 0;
    //         cell_mixer_->stop();
    //     }
    // }
}