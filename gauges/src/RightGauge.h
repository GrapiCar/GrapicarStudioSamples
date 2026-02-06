#ifndef _RIGHTGAUGE_H_
#define _RIGHTGAUGE_H_

#include "grapi/runtime/action.h"

class RightGauge : public grapi::runtime::Action 
{
public:
    SET_ACTION_INSTANCE(RightGauge);

    RightGauge(const grapi::base::String& id, const grapi::base::TypeInfo* type_info = &kTypeInfo);
    virtual ~RightGauge();

    virtual void start() override;
    virtual void update(const vfloat delta_time) override;

    /** @brief 현재 RPM 값 (0~1). LeftGauge(속도)가 참조. */
    static float getRpmNormalized();

private:
    grapi::runtime::DisplayObject* right = nullptr;
    vfloat baseY_ = 0.f;    // 시작 시 Y (현재위치 ~ baseY_ + 400)
    vfloat simTime_ = 0.f;  // RPM 시뮬레이션용 시간

    void setupRightGauge();
    void updateRightGauge(const vfloat delta_time);
};

#endif