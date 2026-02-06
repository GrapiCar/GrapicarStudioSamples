#ifndef _FIRST_H_
#define _FIRST_H_

#include "grapi/runtime/action.h"
#include "grapi/runtime/nine_patch_image.h"

class first : public grapi::runtime::Action 
{
public:
    SET_ACTION_INSTANCE(first);

    first(const grapi::base::String& id, const grapi::base::TypeInfo* type_info = &kTypeInfo);
    virtual ~first();

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