#ifndef _CELL01_H_
#define _CELL01_H_

#include "grapi/runtime/action.h"
#include "grapi/runtime/cell_image_mixer.h"

class cell01 : public grapi::runtime::Action 
{
public:
    SET_ACTION_INSTANCE(cell01);

    cell01(const grapi::base::String& id, const grapi::base::TypeInfo* type_info = &kTypeInfo);
    virtual ~cell01();

    virtual void start() override;
    virtual void update(const vfloat delta_time) override;

private:
    void setupCell();
    void updateCell();

private:
    grapi::runtime::CellImageMixer* cell_mixer_ = nullptr;
    int current_state_ = 0;
};

#endif