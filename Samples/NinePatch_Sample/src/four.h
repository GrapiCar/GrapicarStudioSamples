#ifndef _FOUR_H_
#define _FOUR_H_

#include "grapi/runtime/action.h"
#include "grapi/runtime/nine_patch_image.h"
#include "grapi/runtime/text.h"

class four : public grapi::runtime::Action 
{
public:
    SET_ACTION_INSTANCE(four);

    four(const grapi::base::String& id, const grapi::base::TypeInfo* type_info = &kTypeInfo);
    virtual ~four();

    virtual void start() override;
    virtual void update(const vfloat delta_time) override;

    private:
    void setupImage();
    void updateImage(const vfloat delta_time);
    grapi::runtime::NinePatchImage* image_ = nullptr;
    grapi::runtime::Text* text_ = nullptr;
    glm::vec2 originalSize_ = glm::vec2(0.0f, 0.0f);
    float aspectRatio_ = 1.0f;
};

#endif