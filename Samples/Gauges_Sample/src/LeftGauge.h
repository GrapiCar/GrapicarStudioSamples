#ifndef _LEFTGAUGE_H_
#define _LEFTGAUGE_H_

#include "grapi/runtime/action.h"

class LeftGauge : public grapi::runtime::Action 
{
public:
    SET_ACTION_INSTANCE(LeftGauge);

    LeftGauge(const grapi::base::String& id, const grapi::base::TypeInfo* type_info = &kTypeInfo);
    virtual ~LeftGauge();

    virtual void start() override;
    virtual void update(const vfloat delta_time) override;

private:
    grapi::runtime::DisplayObject* left = nullptr;
    vfloat baseY_ = 0.f;          // 시작 시 Y (현재위치 ~ baseY_ + 400)
    vfloat currentSpeed_ = 0.f;   // 0~1, 속도 게이지용
    vfloat speedTarget_ = 0.f;    // 목표 (RPM 따라가되 오버드라이브 허용)

    void setupLeftGauge();
    void updateLeftGauge(const vfloat delta_time);
};

#endif