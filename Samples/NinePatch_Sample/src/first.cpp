#include <iostream>

#include "grapi/runtime/display_object.h"
#include "grapi/runtime/transform.h"
#include "first.h"
#include "grapi/runtime/nine_patch_image.h"
#include "grapi/runtime/utils.h"

first::first(const grapi::base::String& id, const grapi::base::TypeInfo* type_info) : grapi::runtime::Action(id, type_info) {
}

first::~first() {
}

void first::start() {
    // Scene 에 추가될 때 한번만 실행된다.
    setupImage();
}

void first::update(const vfloat delta_time) {
    // Update 로직을 여기에 구현하세요
    updateImage(delta_time);    
}


void first::setupImage() {
    // NinePatchImage 설정 로직을 여기에 구현하세요
    grapi::runtime::DisplayObject* target = grapi::runtime::findObjectByName("firstBox");

    if(!target) {
        std::cout << "Target object not found!" << std::endl;
        return ;
    }


    grapi::runtime::NinePatchImage* ninePatch = target->getComponent<grapi::runtime::NinePatchImage>();

    if(!ninePatch) {
        std::cout << "NinePatchImage component not found!" << std::endl;
        return ;
    }

    image_ = ninePatch;
    originalSize_ = image_->getSize();
    aspectRatio_ = originalSize_.x / originalSize_.y;
    image_->setSize(glm::vec2(0.1f, 0.1f));
}

void first::updateImage(const vfloat delta_time) {
    // NinePatchImage 업데이트 로직을 여기에 구현하세요
     vfloat prevWidth = image_->getSize().x;
    vfloat prevHeight = image_->getSize().y;

    if(originalSize_.x > originalSize_.y) {
        // 가로가 더 긴 경우: 가로가 원래 크기가 될 때까지 커짐
        if(prevWidth < originalSize_.x) {   
            vfloat newWidth = prevWidth + 1.0f * delta_time;
            if(newWidth > originalSize_.x) newWidth = originalSize_.x;
            vfloat newHeight = newWidth / aspectRatio_;
            image_->setSize(glm::vec2(newWidth, newHeight));
        }
    } else {
        // 세로가 더 긴 경우: 세로가 원래 크기가 될 때까지 커짐
        if(prevHeight < originalSize_.y) {   
            vfloat newHeight = prevHeight + 1.0f * delta_time;
            if(newHeight > originalSize_.y) newHeight = originalSize_.y;
            vfloat newWidth = newHeight * aspectRatio_;
            image_->setSize(glm::vec2(newWidth, newHeight));
        }
    }
}