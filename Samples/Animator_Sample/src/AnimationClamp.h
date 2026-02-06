#ifndef _ANIMATIONCLAMP_H_
#define _ANIMATIONCLAMP_H_

#include "grapi/runtime/action.h"

class AnimationClamp : public grapi::runtime::Action 
{
public:
    SET_ACTION_INSTANCE(AnimationClamp);

    AnimationClamp(const grapi::base::String& id, const grapi::base::TypeInfo* type_info = &kTypeInfo);
    virtual ~AnimationClamp();

    virtual void start() override;
    virtual void update(const vfloat delta_time) override;

    private:
    void setupAnimation();
    void updateAnimation(const vfloat delta_time);
};

#endif