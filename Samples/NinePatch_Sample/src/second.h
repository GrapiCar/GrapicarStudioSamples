#ifndef _SECOND_H_
#define _SECOND_H_

#include "grapi/runtime/action.h"
#include "grapi/runtime/nine_patch_image.h"
class second : public grapi::runtime::Action 
{
public:
    SET_ACTION_INSTANCE(second);

    second(const grapi::base::String& id, const grapi::base::TypeInfo* type_info = &kTypeInfo);
    virtual ~second();

    virtual void start() override;
    virtual void update(const vfloat delta_time) override;

    private: 
    void setupImage();
    void updateImage(const vfloat delta_time);
    grapi::runtime::NinePatchImage* image_ = nullptr;
    glm::vec2 originalSize_ = glm::vec2(0.0f, 0.0f);
    float aspectRatio_ = 1.0f;
};

#endif