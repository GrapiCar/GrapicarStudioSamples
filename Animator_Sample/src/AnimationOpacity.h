#ifndef _ANIMATIONOPACITY_H_
#define _ANIMATIONOPACITY_H_

#include "grapi/runtime/action.h"

class AnimationOpacity : public grapi::runtime::Action 
{
public:
    SET_ACTION_INSTANCE(AnimationOpacity);

    AnimationOpacity(const grapi::base::String& id, const grapi::base::TypeInfo* type_info = &kTypeInfo);
    virtual ~AnimationOpacity();

    virtual void start() override;
    virtual void update(const vfloat delta_time) override;

    private:
    void setupAnimation();
    void updateAnimation(const vfloat delta_time);
};

#endif