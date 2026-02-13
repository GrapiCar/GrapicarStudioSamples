#ifndef _SPEED_NUMBER_H_
#define _SPEED_NUMBER_H_

#include "grapi/runtime/action.h"

class speed_number : public grapi::runtime::Action 
{
public:
    SET_ACTION_INSTANCE(speed_number);

    speed_number(const grapi::base::String& id, const grapi::base::TypeInfo* type_info = &kTypeInfo);
    virtual ~speed_number();

    virtual void start() override;
    virtual void update(const vfloat delta_time) override;

    private:
    void updateVelocity(const vfloat delta_time);
    void updatePosition(int velocity);
    void updateNumberDisplay(int velocity);
    grapi::runtime::DisplayObject* number = nullptr;
    grapi::runtime::Transform* transform = nullptr;

    grapi::runtime::DisplayObject* hundred[10] = {nullptr};
    grapi::runtime::DisplayObject* ten[10] = {nullptr};
    grapi::runtime::DisplayObject* one[10] = {nullptr};

    static constexpr int kMaxVelocity = 260;
    static constexpr vfloat kDuration = 3.2f;
    static constexpr vfloat kPositionOffsetX = 47.0f;
    
    vfloat velocity_ = 0.0f;
    vfloat direction_ = 1.0f;
    vfloat initial_position_x_ = 0.0f;
    bool position_adjusted_ = false;
};

#endif