#ifndef _ANIMATIONWITHCHILD_H_
#define _ANIMATIONWITHCHILD_H_

#include "grapi/runtime/action.h"

class AnimationWithChild : public grapi::runtime::Action 
{
public:
    SET_ACTION_INSTANCE(AnimationWithChild);

    AnimationWithChild(const grapi::base::String& id, const grapi::base::TypeInfo* type_info = &kTypeInfo);
    virtual ~AnimationWithChild();

    virtual void start() override;
    virtual void update(const vfloat delta_time) override;

    private:
    void setupAnimation();
    void updateAnimation(const vfloat delta_time);
};

#endif