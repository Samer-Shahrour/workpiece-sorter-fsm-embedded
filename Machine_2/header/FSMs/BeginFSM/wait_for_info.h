#pragma once

#include "BaseStateBegin.h"

class Wait_for_info_Begin : public BaseStateBegin {

    void info_received()override;
    void m2_lbb_blocked() override;
    void error() override;
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;

};


