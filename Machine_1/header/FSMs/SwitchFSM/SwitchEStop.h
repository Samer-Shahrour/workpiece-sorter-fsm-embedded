#pragma once
#include "BaseStateSwitch.h"

class SwitchEStop : public BaseStateSwitch{

public:
    void estop_ok() override;
};
