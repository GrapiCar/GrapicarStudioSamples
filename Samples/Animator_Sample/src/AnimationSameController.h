#ifndef _ANIMATIONSAMECONTROLLER_H_
#define _ANIMATIONSAMECONTROLLER_H_

#include "grapi/runtime/action.h"

class AnimationSameController : public grapi::runtime::Action 
{
public:
    SET_ACTION_INSTANCE(AnimationSameController);

    AnimationSameController(const grapi::base::String& id, const grapi::base::TypeInfo* type_info = &kTypeInfo);
    virtual ~AnimationSameController();

    virtual void start() override;
    virtual void update(const vfloat delta_time) override;

    private:
    void setupAnimation();
    void updateAnimation(const vfloat delta_time);
};

#endif