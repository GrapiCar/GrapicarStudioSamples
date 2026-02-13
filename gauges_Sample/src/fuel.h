#ifndef _FUEL_H_
#define _FUEL_H_

#include "grapi/runtime/action.h"

class fuel : public grapi::runtime::Action 
{
public:
    SET_ACTION_INSTANCE(fuel);

    fuel(const grapi::base::String& id, const grapi::base::TypeInfo* type_info = &kTypeInfo);
    virtual ~fuel();

    virtual void start() override;
    virtual void update(const vfloat delta_time) override;

    private:
    grapi::runtime::DisplayObject* gauge = nullptr;
    grapi::runtime::Transform* transform = gauge->getTransform();
    
    vfloat current_y_ = 0.0f;
    vfloat direction_ = -1.0f;  // 1: -592->0, -1: 0->-592
    static constexpr vfloat kDuration = 2.2f;
    static constexpr vfloat kMinY = -231.0f;
    static constexpr vfloat kMaxY = 233.0f;
};

#endif