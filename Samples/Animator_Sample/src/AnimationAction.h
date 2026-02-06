#ifndef _ANIMATIONACTION_H_
#define _ANIMATIONACTION_H_

#include "grapi/runtime/action.h"

class AnimationAction : public grapi::runtime::Action 
{
public:
    SET_ACTION_INSTANCE(AnimationAction);

    AnimationAction(const grapi::base::String& id, const grapi::base::TypeInfo* type_info = &kTypeInfo);
    virtual ~AnimationAction();

    virtual void start() override;
    virtual void update(const vfloat delta_time) override;
    
    private:
    void setupAnimation();
    void updateAnimation(const vfloat delta_time);
};



#endif