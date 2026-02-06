#ifndef _CLUSTER_H_
#define _CLUSTER_H_

#include "grapi/runtime/action.h"
#include "grapi/runtime/animator.h"
#include "grapi/runtime/display_object.h"

class Cluster : public grapi::runtime::Action 
{
public:
    SET_ACTION_INSTANCE(Cluster);

    Cluster(const grapi::base::String& id, const grapi::base::TypeInfo* type_info = &kTypeInfo);
    virtual ~Cluster();

    virtual void start() override;
    virtual void update(const vfloat delta_time) override;

private:
    // 0=Eco, 1=Normal(Nomal), 2=Sport
    int currentMode = 0;
    int previousMode = -1;
    double modeTransitionTimer = 0.0;
    const double modeTransitionDuration = 0.35;
    bool isTransitioning = false;
    bool prev_m_ = false;

    grapi::runtime::DisplayObject* ecoMode = nullptr;
    grapi::runtime::DisplayObject* normalMode = nullptr;   // 씬 내 객체 이름은 "Nomal"
    grapi::runtime::DisplayObject* sportMode = nullptr;

    grapi::runtime::Animator* ecoModeAnimator = nullptr;
    grapi::runtime::Animator* normalModeAnimator = nullptr;
    grapi::runtime::Animator* sportModeAnimator = nullptr;

    void setupCluster();
    void changeMode(int newMode);
    void updateMode();
    void updateModeTransition(const vfloat delta_time);
};

#endif
