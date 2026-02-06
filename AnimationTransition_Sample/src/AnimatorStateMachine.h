#ifndef _ANIMATORSTATEMACHINE_H_
#define _ANIMATORSTATEMACHINE_H_

#include "grapi/runtime/action.h"
#include "grapi/runtime/animator.h"

class AnimatorStateMachine : public grapi::runtime::Action 
{
public:
    SET_ACTION_INSTANCE(AnimatorStateMachine);

    AnimatorStateMachine(const grapi::base::String& id, const grapi::base::TypeInfo* type_info = &kTypeInfo);
    virtual ~AnimatorStateMachine();

    virtual void start() override;
    virtual void update(const vfloat delta_time) override;

    int state = 0;

    private:
    grapi::runtime::Animator* animator = nullptr;
    bool* isMusic = nullptr;
    bool* isNAv = nullptr;
    void handleKeyPress();
    void setupUpdate(const int state);
};

#endif