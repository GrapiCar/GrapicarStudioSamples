#ifndef _CELL03_H_
#define _CELL03_H_

#include "grapi/runtime/action.h"

class cell03 : public grapi::runtime::Action 
{
public:
    SET_ACTION_INSTANCE(cell03);

    cell03(const grapi::base::String& id, const grapi::base::TypeInfo* type_info = &kTypeInfo);
    virtual ~cell03();

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