#ifndef _ANGLE_H_
#define _ANGLE_H_

#include "grapi/runtime/action.h"
#include "grapi/runtime/arc.h"

class angle : public grapi::runtime::Action 
{
public:
    SET_ACTION_INSTANCE(angle);

    angle(const grapi::base::String& id, const grapi::base::TypeInfo* type_info = &kTypeInfo);
    virtual ~angle();

    virtual void start() override;
    virtual void update(const vfloat delta_time) override;

private:
    void setupArc();
    void updateArc(const vfloat delta_time);
    grapi::runtime::Arc* arc_ = nullptr;
    vfloat delay_time_ = 0.0f;
};

#endif