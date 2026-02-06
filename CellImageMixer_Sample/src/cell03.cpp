#include <iostream>

#include "grapi/runtime/display_object.h"
#include "grapi/runtime/transform.h"
#include "grapi/runtime/cell_image_mixer.h"
#include "grapi/runtime/utils.h"
#include "cell03.h"
#include "grapi/runtime/input_state.h"

using namespace grapi::runtime;
using namespace grapi::base;

cell03::cell03(const grapi::base::String& id, const grapi::base::TypeInfo* type_info) : grapi::runtime::Action(id, type_info) {
    current_state_ = 0;
}

cell03::~cell03() {
}

void cell03::start() {
    setupCell();  
}

void cell03::update(const vfloat delta_time) {
    InputState::update();  // 매 프레임마다 InputState 업데이트
    updateCell();
}

void cell03::setupCell()
{
    // 부모 객체의 자식들을 순회하여 CellImageMixer 컴포넌트 찾기
    grapi::runtime::DisplayObject* target = grapi::runtime::findObjectByName("AverageCell");

    if(!target) {
        std::cout << "Cannot find AverageCell object!" << std::endl;
        return;
    }

    std::cout << "This Object Name: " << this->getParent()->getName() << std::endl;

    grapi::runtime::CellImageMixer* mixer = target->getComponent<grapi::runtime::CellImageMixer>();

    if(!mixer) {
        std::cout << "Cannot find CellImageMixer component!" << std::endl;
        return;
    }

    cell_mixer_ = mixer;

    // cell_mixer_->setStartIndex(3);
    // cell_mixer_->setEndIndex(6);

    std::cout << "Start Index: " << cell_mixer_->getStartIndex() << std::endl;
    std::cout << "End Index: " << cell_mixer_->getEndIndex() << std::endl;

    cell_mixer_->play(true);
    
}

void cell03::updateCell()
{
    if (cell_mixer_ == nullptr)
    {
        return;
    }

    if(cell_mixer_->getCurrIndex() < cell_mixer_->getStartIndex()) {
        cell_mixer_->setCurrIndex(cell_mixer_->getStartIndex());
    }

    if(cell_mixer_->getCurrIndex() > cell_mixer_->getEndIndex()) {
        cell_mixer_->setCurrIndex(cell_mixer_->getEndIndex());
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