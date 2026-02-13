#ifndef _SPEED_NEEDLE_PIVOT_H_
#define _SPEED_NEEDLE_PIVOT_H_

#include "grapi/runtime/action.h"

namespace grapi {
namespace runtime {
    class DisplayObject;
    class Transform;
}
}

class speed_needle_pivot : public grapi::runtime::Action 
{
public:
    SET_ACTION_INSTANCE(speed_needle_pivot);

    speed_needle_pivot(const grapi::base::String& id, const grapi::base::TypeInfo* type_info = &kTypeInfo);
    virtual ~speed_needle_pivot();

    virtual void start() override;
    virtual void update(const vfloat delta_time) override;

    
    private:
    static constexpr vfloat kDuration = 3.2f;
    static constexpr vfloat kMinZ = -233.0f;
    static constexpr vfloat kMaxZ = -0.0f;
    
    grapi::runtime::DisplayObject* pivot = nullptr;
    grapi::runtime::Transform* transform = nullptr;
    
    vfloat current_z_ = 0.0f;
    vfloat direction_ = 1.0f;


};

#endif