#pragma once
#include "BaseStateSwitch.h"

class SwitchError : public BaseStateSwitch{

public:
    void error_ok() override;
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
    void lbc_free() override;
    void lbc_blocked() override;
};
